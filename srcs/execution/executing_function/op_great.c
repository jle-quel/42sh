//
// Created by Alexandre ROULIN on 11/11/17.
//

#include <sh.h>

void		jobs_op_great(t_node *node)
{
	int			fildes;

	fildes = open(node->right->content->command[0], OPTION_GREAT, 0644);
	if (node->content->command[0][0] == '&')
	{
		dup2(fildes, STDOUT_FILENO);
		dup2(fildes, STDERR_FILENO);
	}
	else if (ft_isdigit(node->content->command[0][0]))
	{
		dup2(fildes, ft_atoi(node->content->command[0]));
	}
	else
	{
		dup2(fildes, STDOUT_FILENO);
	}
}

uint8_t					op_great(t_node *node, t_jobs *jobs, int info)
{
	log_debug("VALUE GREAT %d", info);

	if (info & FORK)
	{
		if ((jobs = new_jobs(jobs)) == NULL)
			return (var_return(255));
		jobs->process = my_fork(jobs, node, info);
		if (jobs->process->pid)
		{
			my_wait(jobs);
		}
		else
		{
			jobs->process->pid = getpid();
			jobs_op_great(node);
			execute_node(node->left, jobs, info ^ FORK);
		}
	}
	else
	{
		jobs_op_great(node);
		execute_node(node->left, jobs, info);
	}
	return (1);
}