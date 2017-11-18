/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <aroulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 01:04:58 by aroulin           #+#    #+#             */
/*   Updated: 2017/11/18 14:03:20 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

/*
*************** PRIVATE ********************************************************
*/

static void		error(char *str)
{
	struct stat	buf;

	if (lstat(str, &buf) != -1)
	{
		if (S_ISDIR(buf.st_mode))
		{
			error_msg(S42H, "Is a directory: ", str);
			kill(getppid(), SIGCHLD);
			perror("das");
			exit(var_return(126));
		}
		else if (!access(str, F_OK) && access(str, X_OK) == -1)
		{
			error_msg(S42H, "Permission denied: ", str);
			kill(getppid(), SIGCHLD);
			perror("das");
			exit(var_return(126));
		}
	}
	else
	{
		error_msg(S42H, "command not found: ", str);
		log_info("%d == kill(%d, SIGCHLD)", kill(getppid(), SIGCHLD), getppid());
		perror("das");
		exit(var_return(127));
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
	if (access(command[0], X_OK) == -1)
	{
		log_info("%d == kill(%d, SIGCHLD)", kill(getppid(), SIGCHLD), getppid());
		log_info("exit(%d)", 127);
		exit(127);
	}
	else
		execve(command[0], command, env) == -1 ? error(command[0]) : 0;
}