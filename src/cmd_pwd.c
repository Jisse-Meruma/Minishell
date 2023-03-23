/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/23 11:50:15 by mbernede      #+#    #+#                 */
/*   Updated: 2023/03/23 12:28:45 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	cmd_pwd(void)
{
	char	*envpwd;

	envpwd = getenv("PWD");
	if (envpwd)
		ft_putstr_fd(envpwd, 1);
	else
	{
		free(envpwd);
		envpwd = getcwd(NULL, 0);
		ft_putstr_fd(envpwd, 1);
		printf("\n");
	}
	free(envpwd);
}