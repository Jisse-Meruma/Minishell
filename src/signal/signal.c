/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 16:24:33 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/28 18:16:19 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#define CHILD 0

extern int	g_signal;

void	f_sigmain(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf("\n");
		g_signal = 130;
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		g_signal = 131;
}

void	mainsignal(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, f_sigmain);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == 1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == 2)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == 3)
	{
		signal(SIGINT, f_sigmain);
		signal(SIGQUIT, SIG_DFL);
	}
}
