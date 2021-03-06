/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_delete_here.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 17:36:48 by aroulin           #+#    #+#             */
/*   Updated: 2017/11/17 17:17:47 by gbourson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

void		delete_here(t_read **read_std, unsigned long buff)
{
	t_cmd		*kill;

	kill = (*read_std)->cmd;
	(*read_std)->cmd = (*read_std)->cmd->next;
	if ((*read_std)->cmd->prev->prev)
		(*read_std)->cmd->prev->prev->next = (*read_std)->cmd;
	(*read_std)->cmd->prev = (*read_std)->cmd->prev->prev;
	kill->next = NULL;
	kill->prev = NULL;
	add_outstanding(kill, buff, 0);
	(*read_std)->print = 2;
}

int			key_delete_here(t_read **read_std, unsigned long buff)
{
	if ((*read_std)->completion)
	{
		memdel_completion(&((*read_std)->tab_));
		(*read_std)->print = 2;
	}
	else if ((*read_std)->history_search)
	{
		memdel_lfh(&((*read_std)->hist_search));
		(*read_std)->print = 2;
	}
	if (!(*read_std)->history_search && (*read_std)->cmd->c)
		delete_here(read_std, buff);
	return (1);
}
