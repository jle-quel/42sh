/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <aroulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 19:09:46 by aroulin           #+#    #+#             */
/*   Updated: 2017/11/16 16:20:05 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

t_jobs				**jobs_table(void)
{
	static t_jobs		*jobs;

	return (&jobs);
}

void				update_jobs(int status)
{
	log_trace("/!\\  [PROCESS LL BE UPDATE] /!\\");
	if (WIFEXITED(status))
		var_return(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		var_return(WTERMSIG(status) + 128);
	else if (WIFSTOPPED(status))
		var_return(WSTOPSIG(status) + 128);
	else if (WIFCONTINUED(status))
		;
}


void				handler_sigchld(int sig)
{
	int			pid;
	int			status;

	log_trace("/!\\  [SIGCHLD RECEPTION %d] /!\\", sig);
	pid = waitpid(-1, &status, WUNTRACED);
	place_status(pid, status);
}
