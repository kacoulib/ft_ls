/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 15:42:56 by kacoulib          #+#    #+#             */
/*   Updated: 2017/09/09 15:43:07 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					ft_check_flag(char c)
{
	t_master		*master;

	if (!(master = ft_get_or_create_master()))
		return (0);
	return (ft_indexof(master->flags, c) > -1);
}

t_master			*ft_get_or_create_master(void)
{
	static t_master	*master = NULL;

	if (master)
		return (master);
	if (!(master = (t_master *)malloc(sizeof(t_master) + 1)))
		return (NULL);
	return (master);
}

static int			ft_init_params(t_file *tmp_master, char **av, int i,
	int l_len[])
{
	t_file			*tmp;

	if (!(tmp = ft_init_folder((!av[i]) ? "." : av[i], tmp_master, NULL)))
		return (ft_set_error(tmp_master, "error initialize folder", 0));
	if (!ft_is_dir(tmp->name) && !ft_is_file(tmp->name))
		return (ft_set_error(tmp_master, ft_strjoin(tmp->name, ": "), "open"));
	i = ft_strlen(tmp->name);
	tmp->path = tmp->name;
	if (ft_is_dir(tmp->name) && tmp->name[i] != '/')
		tmp->type = 4;
	else
		ft_set_sb_and_long(tmp, l_len);
	if (!tmp_master->files)
		tmp_master->files = tmp;
	else
		ft_push_file(tmp_master->files, tmp);
	return (1);
}

t_master			*ft_init_master(int *ac, char **av, t_file *tmp_master,
	int l_len[])
{
	int				i;
	t_master		*master;

	i = 0;
	if (!(master = ft_get_or_create_master()))
		return (NULL);
	master->flags = ft_strdup("alRrtuG");
	master->errors = ft_init_folder(NULL, NULL, NULL);
	if (*ac < 1 || (i = ft_set_flags(master, tmp_master, av, 0)) < -1)
		return (NULL);
	master->is_multi = (av[i] && av[i + 1]) ? 1 : 0;
	*ac += (i > -1 && !av[i]) ? 1 : 0;
	while (i > -1 && i < *ac)
	{
		ft_init_params(tmp_master, av, i, l_len);
		i++;
	}
	return (master);
}

t_file				*ft_init_folder(char *name, t_file *parent, t_file *prev)
{
	t_file			*file;
	struct stat		*sb;

	file = (t_file *)malloc(sizeof(t_file) + 1);
	sb = (struct stat*)malloc(sizeof(struct stat) + 1);
	if (!file || !sb)
		return (NULL);
	file->name = (name) ? ft_strdup(name) : NULL;
	file->path = NULL;
	file->info = NULL;
	file->size = 0;
	file->type = 8;
	file->sb = sb;
	file->files = NULL;
	file->parent = parent;
	file->errors = NULL;
	file->next = NULL;
	file->prev = prev;
	return (file);
}
