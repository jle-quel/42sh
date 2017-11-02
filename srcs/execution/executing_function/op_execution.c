//
// Created by Alexandre ROULIN on 10/31/17.
//

#include <sh.h>

uint8_t					do_execution(t_node *node, int info)
{
	t_jobs		*jobs;

	if (FORK & info)
	{
		if ((jobs = new_jobs()) == NULL)
			return (var_return(255));
		jobs->process = my_fork(jobs, node, info);
		if (jobs->process->pid > 0) // father
			my_wait(jobs);
		else if (jobs->process->pid == 0) // fils
			my_execve(node->content->command, get_real_env(node));
	}
	else
		my_execve(node->content->command, get_real_env(node));
	return (1);
}

uint8_t					op_execution(t_node *node, int info)
{
	if (check_if_builtin(node, info) >= 0)
	{
		if (!(info & FORK))
			exit(var_return(-1));
	}
	else
	{
		do_execution(node, info);
	}
	return (var_return(-1));
}

