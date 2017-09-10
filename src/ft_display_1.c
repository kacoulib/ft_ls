/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/03 17:38:48 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/03 17:39:06 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int			ft_put_no_color(char *str, int type, char *link)
{
	if (type == 10)
	{
		ft_putstr(str);
		if (link)
		{
			ft_putstr(" -> ");
			ft_putstr(link);
		}
		return (1);
	}
	ft_putstr(str);
	return (1);
}

int					ft_display_color(t_file *file)
{
	int				(*fn_display)(char *, int, char*);
	char			tmp[256];

	fn_display = ft_check_flag('G') ? &ft_putfile : &ft_put_no_color;
	if (file->type == 10)
	{
		if (ft_check_flag('l'))
		{
			ft_bzero(tmp, 256);
			readlink(file->path, tmp, 256);
			fn_display(file->name, file->type, tmp);
		}
		else
			fn_display(file->name, file->type, NULL);
	}
	else if ((file->sb->st_mode & S_IWOTH))
		fn_display(file->name, 32, NULL);
	else if ((file->sb->st_mode & S_IXOTH) && file->type != 4)
		fn_display(file->name, 16, NULL);
	else
		fn_display(file->name, file->type, NULL);
	ft_putchar('\n');
	return (1);
}
