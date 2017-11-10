/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:22:05 by aroulin           #+#    #+#             */
/*   Updated: 2017/11/09 14:53:46 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>



/*
*************** PRIVATE ********************************************************
*/

static size_t	get_length(char **argv, size_t length)
{
	return ((argv && argv[length]) ? get_length(argv, length + 1) : length);
}

/*
*************** PUBLIC *********************************************************
*/

uint8_t			builtin_exit(t_node *node, int info __attribute__((unused)))
{
	size_t		length;
	int			var;

	if ((length = get_length(node->content->command, 0)) == 2)
	{
		if (ft_strisdigit(node->content->command[1]))
			var = ft_atoi(node->content->command[1]);
		else
		{
			error_builtin(EXIT, NUM_REQUIRED, node->content->command[1]);
			var = 255;
		}
		b_write_history_in_file(get_str_from_history());
		exit(var);
	}
	else if (length > 2)
		return (error_builtin(EXIT, TOO_MANY_ARGS, NULL));
	else
		exit_();
	return (0);
}
