/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_dless.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quel <jle-quel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 16:14:51 by jle-quel          #+#    #+#             */
/*   Updated: 2017/12/15 19:20:56 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/*
*************** PRIVATE ********************************************************
*/

static int		get_fildes(char *str)
{
	int			fildes;

	if ((fildes = open(str, O_RDONLY)) == -1)
	{
		check_path(str);
		return (-1);
	}
	return (fildes);
}

/*
*************** PUBLIC *********************************************************
*/

int				op_dless(t_parsing *node)
{
	int			fildes;

	if ((fildes = get_fildes(node->heredoc)) == -1)
		return (0);
	if (dup2(fildes, STDIN_FILENO) == -1)
	{
		error_msg(S42H, BAD_FD, NULL);
		return (0);
	}
	close(fildes);
	remove(node->heredoc);
	return (1);
}
