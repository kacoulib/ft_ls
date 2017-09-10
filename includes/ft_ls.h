/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 16:38:11 by kacoulib          #+#    #+#             */
/*   Updated: 2017/01/18 16:39:45 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../lib/libft/libft.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/ioctl.h>

typedef struct		s_file
{
	char			*name;
	char			*path;
	char			*info;
	char			*l[7];
	int				size;
	short			type;
	struct stat		*sb;
	struct s_file	*files;
	struct s_file	*parent;
	struct s_file	*errors;
	struct s_file	*next;
	struct s_file	*prev;
}					t_file;

typedef struct		s_master
{
	char			*flags;
	short			is_multi;
	short			is_first;
	short			l_len[7];
	struct s_file	*files;
	struct s_file	*errors;
}					t_master;

int					ft_check_flag(char c);
int					ft_display_color(t_file *file);
int					ft_display_folder_files(t_file *folder, int l_len[]);
int					ft_display_result(t_file *file, int l_len[], int is_multi,
	int is_first);
t_master			*ft_get_or_create_master(void);

t_file				*ft_init_folder(char *name, t_file *parent, t_file *prev);
t_master			*ft_init_master(int *ac, char **av, t_file *tmp_master,
	int l_len[]);

char				*ft_padding(char *s, int offset, char direction);
int					ft_parse_dir(t_file *file, DIR *tmp, int l_len[],
	t_master *master);
int					ft_rev_file(t_file **file);
int					ft_rev_list(t_file **file);
int					ft_set_error(t_file *file, char *s, char *type);
int					ft_set_extra_info(t_file *file, int l_len[]);
int					ft_set_flags(t_master *master, t_file *file, char **av,
	int i);
int					ft_sort_params(char **av, int i);
int					set_parse_params(t_file *master, char **av,
	int l_len[], int i);
int					ft_set_sb_and_long(t_file *file, int l_len[]);
int					ft_sort_settings(t_file **file);
int					ft_sort_by_last_modify(t_file **file);
int					ft_sort_lexico(t_file **file);
int					ft_swap_file(t_file **file, t_file *current,
	t_file *tmp);
int					ft_push_file(t_file *head, t_file *file);
int					ft_display_errors(t_file *file);

#endif
