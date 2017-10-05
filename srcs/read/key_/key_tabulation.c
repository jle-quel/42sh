/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_tabulation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/12 17:39:56 by aroulin           #+#    #+#             */
/*   Updated: 2017/08/23 13:37:20 by aroulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

int			key_tab(t_read **read_std,
                       unsigned long buff __attribute__((unused)))
{
	if ((*read_std)->history_search && bip())
	{
		memdel_lfh(&((*read_std)->hist_search));
	}
	if ((*read_std)->completion)
	{
		log_debug("Continue completion");
		move_completion_right(read_std);

	}
	else
	{
		log_debug("Init completion");
		memdel_completion(&((*read_std)->tab_));
		init_completion(read_std);
	}
	return (1);
}
