/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 16:37:25 by kacoulib          #+#    #+#             */
/*   Updated: 2017/01/18 16:38:00 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int			ft_parse_dir_recursive(t_file *file, DIR *dir,
	int l_len[], t_master *master)
{
	if (ft_check_flag('R'))
	{
		while (file)
		{
			if (file->type == 4 && ft_strcmp(file->name, ".") != 0)
			{
				if (ft_strcmp(file->name, "..") != 0)
				{
					master->is_first = 0;
					ft_parse_dir(file, dir, l_len, master);
				}
			}
			file = file->next;
		}
	}
	return (1);
}

static int			ft_parse_dir_last_part(t_file *current, struct dirent *tmp,
	int l_len[])
{
	if (tmp)
	{
		if (current->path[ft_strlen(current->path) - 1] != '/')
			current->path = ft_strjoin(current->path, "/");
		else
			current->path = current->path;
		current->path = ft_strjoin(current->path, current->name);
		current->type = tmp->d_type;
	}
	ft_set_sb_and_long(current, l_len);
	return (1);
}

int					ft_parse_dir(t_file *file, DIR *dir, int l_len[],
	t_master *master)
{
	struct dirent	*tmp;
	t_file			*current;

	if ((dir = opendir(file->path)))
	{
		while ((tmp = readdir(dir)))
		{
			if (tmp->d_name[0] != '.' || ft_check_flag('a'))
			{
				if (!(file->files) &&
					((file->files = ft_init_folder(tmp->d_name, file, NULL))))
					current = file->files;
				else if ((current->next =
					ft_init_folder(tmp->d_name, file, current)))
					current = current->next;
				current->path = file->path;
				ft_parse_dir_last_part(current, tmp, l_len);
			}
		}
		closedir(dir);
	}
	else
		ft_set_error(file, file->name, NULL);
	ft_display_result(file, l_len, master->is_multi, master->is_first);
	return (ft_parse_dir_recursive(file->files, dir, l_len, master));
}

static int			ft_set_parse_params(t_master *master, int l_len[])
{
	int				i;
	DIR				*dir;
	t_file			*tmp;

	dir = NULL;
	if (!(tmp = master->files))
		return (-1);
	i = ft_display_folder_files(tmp, l_len);
	master->is_first = (i) ? 0 : 1;
	while (tmp)
	{
		if (tmp->type == 4)
			ft_parse_dir(tmp, dir, l_len, master);
		tmp = tmp->next;
	}
	return (1);
}

int					main(int ac, char **av)
{
	int				l_len[7];
	t_master		*master;
	t_file			*tmp_master;

	if (!(tmp_master = ft_init_folder("master", NULL, NULL)))
		return (-1);
	if (!(master = ft_init_master(&ac, av, tmp_master, l_len)))
		return (-1);
	if (tmp_master->files)
		master->files = tmp_master->files;
	if (tmp_master->errors)
		master->errors = tmp_master->errors;
	if (master->errors)
		ft_display_errors(tmp_master);
	if (!master->files)
		return (0);
	ft_sort_settings(&master->files);
	ft_set_parse_params(master, l_len);
	return (0);
}
