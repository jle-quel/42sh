/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_str_from_history.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 17:03:28 by aroulin           #+#    #+#             */
/*   Updated: 2017/09/23 19:57:24 by aroulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

char		*get_str_from_history(void)
{
	char	*home;

	if (!(home = my_getenv("HOME")))
		return (NULL);
	return (ft_strjoin(home, PATH_HISTORY));
}
