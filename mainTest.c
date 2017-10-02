//
// Created by Alexandre ROULIN on 9/28/17.
//
#define _GNU_SOURCE     /* Get declaration of strsignal() from <string.h> */
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <fcntl.h>
#include <curses.h>
#include <term.h>
#include <stdbool.h>
#include <sys/types.h>
#include <dirent.h>
static int cmdNum;              /* Our position in pipeline */
static void                     /* Handler for various signals */
handler(int sig)
{
	/* UNSAFE: This handler uses non-async-signal-safe functions
	   (fprintf(), strsignal(); see Section 21.1.2) */
if (getpid() == getpgrp())          /* If process group leader */
fprintf(stderr, "Terminal FG process group: %ld\n",
(long) tcgetpgrp(STDERR_FILENO));

		fprintf(stderr, "Process %ld (%d) received signal %d (%s)\n",
		        (long) getpid(), cmdNum, sig, strsignal(sig));
/* If we catch SIGTSTP, it won't actually stop us. Therefore we
   raise SIGSTOP so we actually get stopped. */
if (sig == SIGTSTP)
raise(SIGSTOP);
}
int
main(int argc, char *argv[])
{
	struct sigaction sa;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handler;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		dprintf(2, "sig\n");
	if (sigaction(SIGTSTP, &sa, NULL) == -1)
		dprintf(2, "sig\n");
	if (sigaction(SIGCONT, &sa, NULL) == -1)
		dprintf(2, "sig\n");
	/* If stdin is a terminal, this is the first process in pipeline:
	   print a heading and initialize message to be sent down pipe */
	if (isatty(STDIN_FILENO)) {
		fprintf(stderr, "Terminal FG process group: %ld\n",
		        (long) tcgetpgrp(STDIN_FILENO));
				fprintf(stderr, "Command   PID  PPID  PGRP   SID\n");
		cmdNum = 0;
	} else {            /* Not first in pipeline, so read message from pipe */
		if (read(STDIN_FILENO, &cmdNum, sizeof(cmdNum)) <= 0)
			dprintf(2, "sEOF\n");

	}
	cmdNum++;
			fprintf(stderr, "%4d    %5ld %5ld %5ld %5ld\n", cmdNum,
			        (long) getpid(), (long) getppid(),
			        (long) getpgrp(), (long) getsid(0));
	/* If not the last process, pass a message to the next process */
	if (!isatty(STDOUT_FILENO))   /* If not tty, then should be pipe */
		if (write(STDOUT_FILENO, &cmdNum, sizeof(cmdNum)) == -1)
			dprintf(2, "smsg\n");

	for(;;)             /* Wait for signals */
		pause();
}