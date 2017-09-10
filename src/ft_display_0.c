/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_displays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 19:57:55 by kacoulib          #+#    #+#             */
/*   Updated: 2017/01/23 19:57:57 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		ft_display_single(t_file *file, int l_len[])
{
	int			i;
	char		*tmp;

	if (ft_check_flag('l') && file->type != -1)
	{
		i = -1;
		while (file->l[++i] && l_len[i])
		{
			if (i == 4)
				tmp = ft_padding(file->l[i],
					(l_len[i] - ft_strlen(file->l[i])) + 1, 'r');
			else
				tmp = ft_padding(file->l[i],
					(l_len[i] - ft_strlen(file->l[i])) + 1, 'l');
			ft_putstr(ft_strjoin(tmp, " "));
		}
	}
	ft_display_color(file);
	return (1);
}

static int		ft_display_all_in_folder(t_file *file, int l_len[])
{
	while (file && ft_display_single(file, l_len))
		file = file->next;
	return (1);
}

int				ft_display_folder_files(t_file *folder, int l_len[])
{
	t_file		*tmp;
	int			i;

	tmp = folder;
	i = 0;
	while (tmp)
	{
		if (tmp->type != 4 && ++i)
			ft_display_single(tmp, l_len);
		tmp = tmp->next;
	}
	return (i);
}

int				ft_display_errors(t_file *file)
{
	if (!file || !file->errors)
		return (1);
	ft_sort_lexico(&file->errors);
	while (file->errors)
	{
		ft_putendl(file->errors->name);
		file->errors = file->errors->next;
	}
	return (1);
}

int				ft_display_result(t_file *file, int l_len[], int is_multi,
	int is_first)
{
	ft_sort_settings(&file->files);
	if (!ft_check_flag('R'))
	{
		if (is_multi && file->prev)
			ft_putchar('\n');
		if (is_multi)
			ft_print(file->path, ":", NULL, NULL);
		if (ft_check_flag('l'))
			ft_print("total ", ft_itoa(file->size), NULL, NULL);
	}
	else
	{
		if (!is_first)
			ft_putchar('\n');
		if (!is_first || is_multi)
			ft_print(file->path, ":", NULL, NULL);
		if (ft_check_flag('l') && file->files)
			ft_print("total ", ft_itoa(file->size), NULL, NULL);
	}
	ft_display_errors(file);
	ft_display_all_in_folder(file->files, l_len);
	return (1);
}
