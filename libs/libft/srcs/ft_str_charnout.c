/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_charnout.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <aroulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/01 00:00:21 by aroulin           #+#    #+#             */
/*   Updated: 2016/01/01 00:00:42 by aroulin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

static int	ft_charinstr(char c, char *str)
{
	int	boolean;

	boolean = 0;
	while (*str)
	{
		if (c == *str)
		{
			boolean = 1;
			break ;
		}
		str++;
	}
	return (boolean);
}

char		*ft_str_charnout(char const *s, char *listc, size_t start)
{
	size_t	len;
	size_t	i;
	char	*freshstr;

	len = 0;
	i = 0;
	while (s[i])
		if (!ft_charinstr(s[i++], listc) || i < start)
			len++;
	freshstr = (char *)malloc(len + 1);
	i = 0;
	len = 0;
	if (freshstr != NULL)
	{
		while (s[i])
		{
			if (!ft_charinstr(s[i], listc) || i < start)
				freshstr[len++] = s[i];
			i++;
		}
		freshstr[len] = '\0';
	}
	return (freshstr);
}
