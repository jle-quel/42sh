/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executing_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quel <jle-quel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:15:36 by jle-quel          #+#    #+#             */
/*   Updated: 2017/11/17 15:15:39 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

t_parsing			*find_executing_node(t_parsing *node)
{
	if (node->priority == PRIO_PIPE)
		return (find_executing_node(node->right));
	return (node);
}
