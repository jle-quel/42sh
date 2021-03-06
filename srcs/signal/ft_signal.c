/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aroulin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 19:16:56 by aroulin           #+#    #+#             */
/*   Updated: 2017/12/20 15:20:45 by jle-quel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sh.h>

void				handler_sig(int sig)
{
	set_termios(SET_OLD_TERM);
	reset_signal();
	b_write_history_in_file(get_str_from_history());
	init_rc(NULL);
	kill(0, sig);
}

void				handler_sigint(int sig)
{
	(void)sig;
	signal_reception(SIGINT);
	var_return(1);
	ioctl(0, TIOCSTI, "\2\0");
}

void				handler_sigwinsz(int sig)
{
	(void)sig;
	ioctl(0, TIOCSTI, "\0");
}

void				init_signal(void)
{
	int	i;

	i = -1;
	while (++i < 32)
		signal(i, handler_sig);
	signal(SIGINT, &handler_sigint);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGWINCH, &handler_sigwinsz);
	signal(SIGCHLD, &handler_sigchld);
}

void				reset_signal(void)
{
	int i;

	i = -1;
	while (++i < 32)
		signal(i, SIG_DFL);
}
