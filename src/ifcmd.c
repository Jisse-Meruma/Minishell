/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ifcmd.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/23 11:46:57 by mbernede      #+#    #+#                 */
/*   Updated: 2023/03/23 13:03:24 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	ifcmd(char *argv[], char *envp[])
{
	char	*path;
	pid_t	pid;

	if (!compare(argv[0], "pwd"))
		cmd_pwd();
	else if (!compare(argv[0], "env"))
		cmd_env();
	else
		execute_cmd(argv, envp);
}