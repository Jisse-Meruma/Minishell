/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 16:24:33 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/21 16:24:34 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#define CHILD 0

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
