/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbelazou <sbelazou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 17:47:33 by sbelazou          #+#    #+#             */
/*   Updated: 2017/11/17 16:19:56 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

char				**env_cpy(char **src)
{
	unsigned int	i;
	char			**cpy;

	if (!(cpy = malloc(sizeof(char *) * (ft_tablen(src) + 1))))
		return (NULL);
	i = 0;
	while (src[i])
	{
		cpy[i] = ft_strdup(src[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

char				**init_pwd(char **env)
{
	char			buff[UCHAR_MAX];
	int				i;
	char			*var;

	i = 0;
	if (getcwd(buff, UCHAR_MAX) == NULL)
		return (env);
	if (search_in_tab(env_table(NULL, ENV_REC), "PWD=") == -1)
	{
		var = add_envar("PWD=", buff);
		add_environment(var);
		free(var);
		b_data()->pwd = ft_strdup(buff);
	}
	else
		b_data()->pwd = ft_strdup(buff);
	if (search_in_tab(env_table(NULL, ENV_REC), "OLDPWD=") == -1)
	{
		var = add_envar("OLDPWD", "=");
		add_environment(var);
		free(var);
	}
	b_data()->oldpwd = NULL;
	return (env);
}

signed int			search_in_tab(char **data, char *var)
{
	signed int		i;

	i = 0;
	while (data[i])
	{
		if (ft_strncmp(data[i], var, ft_strlen(var)) == 0)
			return (i);
		i++;
	}
	return (-1);
}
