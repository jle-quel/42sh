/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_del.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:33:09 by aroulin           #+#    #+#             */
/*   Updated: 2017/08/19 20:22:27 by aroulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

int			key_del_fct(t_cmd *cmd)
{
	t_cmd		*kill;

	if (cmd->prev)
	{
		kill = cmd->prev;
		if (cmd->prev->prev)
		{
			cmd->prev->prev->next = cmd;
			cmd->prev = cmd->prev->prev;
		}
		else
			cmd->prev = NULL;
		ft_memdel((void **)&(kill));
		return (1);
	}
	return (0);
}

int			key_del(t_read **read_std)
{
    if ((*read_std)->history_search)
    {
        key_del_fct((*read_std)->hist_search->cmd);
		compare_history(read_std);
        (*read_std)->history_search++;
    }
    else if (key_del_fct((*read_std)->cmd))
    {
        (*read_std)->print = 2;
    }
    else if ((*read_std)->completion)
    {
	    (*read_std)->print = 2;
	    bip();
    }
	else
	    bip();
    return (1);
}