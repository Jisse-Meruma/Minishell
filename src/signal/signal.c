#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#define CHILD 0

int	g_pidchild;

void	f_sig(int sig)
{
	if (sig == SIGINT)
		kill(g_pidchild, SIGKILL);
}

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

void	signal_cmd(t_infos *infos)
{
	if (infos->pid)
	{
		g_pidchild = infos->pid;
		signal(SIGINT, f_sig);
		signal(SIGQUIT, f_sig);
	}
}

void	mainsignal(void)
{
	extern int	rl_catch_signals;

	signal(SIGINT, f_sigmain);
	signal(SIGQUIT, f_sigmain);
	rl_catch_signals = 1;
}
