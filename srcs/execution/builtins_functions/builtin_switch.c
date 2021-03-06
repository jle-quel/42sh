/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_switch.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <aroulin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:22:55 by aroulin           #+#    #+#             */
/*   Updated: 2017/11/20 23:39:18 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

static int		put_in_foreground(t_jobs *jobs)
{
	add_to_first(jobs);
	set_fildes(jobs->process->pgid);
	modify_runing(jobs->process, true);
	modify_foreground(jobs->process, true);
	reset_signal();
	print_jobs_info(jobs, jobs->process, OPT_C);
	kill(-jobs->process->pgid, SIGCONT);
	wait_group(jobs->process, WUNTRACED);
	init_signal();
	set_fildes(getpgid(0));
	update_status(jobs->process);
	update_jobs(jobs->process);
	if (finished_process(jobs->process))
		;
	else
	{
		modify_foreground(jobs->process, false);
		modify_runing(jobs->process, false);
		print_status(jobs, jobs->process);
	}
	return (0);
}

static int		put_in_background(t_jobs *jobs)
{
	if (jobs->process->running == false)
	{
		add_to_first(jobs);
		modify_runing(jobs->process, true);
		modify_foreground(jobs->process, false);
		print_jobs_info(jobs, jobs->process, OPT_C);
		kill(-jobs->process->pgid, SIGCONT);
		wait_group(jobs->process, WCONTINUED);
	}
	return (0);
}

uint8_t			builtin_foreground(t_parsing *node, int info)
{
	int			jobs_spec;
	t_jobs		*jobs;

	(void)info;
	if ((jobs_spec = check_jobs_spec(node->command, FG)) == -1)
		return (1);
	if ((jobs = get_jobs_by_setting(jobs_spec, FG)))
		return (uint8_t)(put_in_foreground(jobs));
	return (1);
}

uint8_t			builtin_background(t_parsing *node, int info)
{
	int			jobs_spec;
	t_jobs		*jobs;

	(void)info;
	if ((jobs_spec = check_jobs_spec(node->command, BG)) == -1)
		return (1);
	if ((jobs = get_jobs_by_setting(jobs_spec, BG)))
		return (uint8_t)(put_in_background(jobs));
	return (1);
}
