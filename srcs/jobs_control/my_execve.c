/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <aroulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 01:04:58 by aroulin           #+#    #+#             */
/*   Updated: 2017/11/18 13:59:44 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/*
*************** PRIVATE ********************************************************
*/

static void		error(char *str)
{
	struct stat	buf;

	lstat(str, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		error_msg("42sh: ", "Is a directory: ", str);
		exit(126);
	}
	else if (!access(str, F_OK) && access(str, X_OK) == -1)
	{
		error_msg("42sh: ", "Permission denied: ", str);
		exit(126);
	}
	else
	{
		error_msg("42sh: ", "command not found: ", str); 
		exit(127);
	}
}

/*
*************** PUBLIC *********************************************************
*/

void			my_execve(char **command, char **env)
{
	reset_signal();
	log_info("[%s] PID [%d] PPID [%d] PGID [%d]",
	command[0], getpid(), getppid(), getpgid(0));
	execve(command[0], command, env) == -1 ? error(command[0]) : 0;
}
