#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#define CHILD 0

// int g_pidchild;

// void	f_sig(int sig)
// {
//     if (sig == SIGINT)
//         kill(g_pidchild, SIGKILL);
// }

// void    signal_cmd(t_infos *infos)
// {
//     if (infos->pid)
//     {
//         printf("creation of the signal hangler on SIGINT\n");
//         g_pidchild = infos->pid;
//         signal(SIGINT, f_sig);
//     }
// }