/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 14:11:22 by aroulin           #+#    #+#             */
/*   Updated: 2017/12/20 15:17:17 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

void			exit_(void)
{
	b_write_history_in_file(get_str_from_history());
	init_rc(NULL);
	exit(var_return(-1));
}
