#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#define CHILD 0

int g_pidchild;

void	f_sig(int sig)
{
    if (sig == SIGINT)
        kill(g_pidchild, SIGKILL);
    if (sig == SIGQUIT)
        ;
}

void	f_sigmain(int sig)
{
    if (sig == SIGINT)
        ;
    if (sig == SIGQUIT)
        ;
}

void    signal_cmd(t_infos *infos)
{
    if (infos->pid)
    {
        g_pidchild = infos->pid;
        signal(SIGINT, f_sig);
        signal(SIGQUIT, f_sig);
    }
}

void    mainsignal(t_infos *infos)
{
    signal(SIGINT, f_sigmain);
    signal(SIGQUIT, f_sigmain);
}