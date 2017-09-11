/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorts2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 17:56:36 by kacoulib          #+#    #+#             */
/*   Updated: 2017/04/02 17:56:40 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_rev_list(t_file **file)
{
	while ((*file)->prev)
		(*file) = (*file)->prev;
	return (1);
}

int			ft_rev_file(t_file **file)
{
	t_file	*prev;
	t_file	*tmp;

	prev = NULL;
	while (*file)
	{
		tmp = (*file);
		*file = (*file)->next;
		tmp->next = prev;
		prev = tmp;
	}
	*file = tmp;
	return (0);
}

int			ft_swap_file(t_file **file, t_file *current, t_file *head)
{
	if (current->prev)
		current->prev->next = current->next;
	if (current->next)
		current->next->prev = current->prev;
	if (head->prev)
		head->prev->next = current;
	current->prev = head->prev;
	head->prev = current;
	current->next = head;
	if (head == (*file))
		(*file) = current;
	return (1);
}
