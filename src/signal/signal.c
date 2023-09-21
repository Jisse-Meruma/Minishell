#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#define CHILD 0

//when ./minishell inside itself multiple time, print the SIGINT for all minishell
void	f_sigmain(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		g_glo.error = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		g_glo.error = 131;
}

void	mainsignal(void)
{
	extern int	rl_catch_signals;

	signal(SIGINT, f_sigmain);
	signal(SIGQUIT, f_sigmain);
	rl_catch_signals = 1;
}
