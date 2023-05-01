/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/01 15:29:50 by mbernede      #+#    #+#                 */
/*   Updated: 2023/05/01 18:00:39 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
// < redirect input
// > redirect output
// << heredoc
// >> append mode

void ft_2dprint(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		printf("%s\n", args[i]);
		++i;
	}
}

// void	show_exec(t_command *commands)
// {
// 	ft_2dprint(commands->cmd_argv);
// 	printf("%s\n", commands->redirects.lst_redirect_read);
// 	printf("%s\n", commands->redirects.lst_redirect_write);
// }


// would be nice calling the commands formated
void	exec_built(t_infos *infos, t_command *commands)
{
	if (!compare(commands->cmd_argv[0], "pwd"))
		cmd_pwd(infos);
	else if (!compare(commands->cmd_argv[0], "echo"))
		cmd_echo(infos, commands->cmd_argv);
	else if (!compare(commands->cmd_argv[0], "env"))
		cmd_env(infos);
	else if (!compare(commands->cmd_argv[0], "getenv"))
		cmd_get_env(infos, commands->cmd_argv[1]);
	else if (!compare(commands->cmd_argv[0], "exit"))
		cmd_exit(infos, commands->cmd_argv);
	else if (!compare(commands->cmd_argv[0], "cd"))
		cmd_cd(infos, commands->cmd_argv[1]);
	else if (!compare(commands->cmd_argv[0], "unset"))
		cmd_unset(infos, commands->cmd_argv[1]);
	else if (!compare(commands->cmd_argv[0], "export"))
		cmd_export(infos, commands->cmd_argv[1]);
	else
		printf("not a builtins , why am I printing ????\n");
}

void		if_builtins(t_command *commands)
{
	if (!ft_strncmp("cd", commands->cmd_argv[0], 3))
	{
		commands->is_built = 1;
		commands->is_built_parent = 1;
	}
	else if (!ft_strncmp("echo", commands->cmd_argv[0], 5))
	{
		commands->is_built = 1;
		commands->is_built_parent = 0;
	}
	else if (!ft_strncmp("env", commands->cmd_argv[0], 4))
	{
		commands->is_built = 1;
		commands->is_built_parent = 0;
	}
	else if (!ft_strncmp("exit", commands->cmd_argv[0], 5))
	{
		commands->is_built = 1;
		commands->is_built_parent = 1;
	}
	else if (!ft_strncmp("export", commands->cmd_argv[0], 7))
	{
		commands->is_built = 1;
		commands->is_built_parent = 1;
	}
	else if (!ft_strncmp("getenv", commands->cmd_argv[0], 7))
	{
		commands->is_built = 1;
		commands->is_built_parent = 0;
	}
	else if (!ft_strncmp("pwd", commands->cmd_argv[0], 4))
	{
		commands->is_built = 1;
		commands->is_built_parent = 0;
	}
	else if (!ft_strncmp("unset", commands->cmd_argv[0], 6))
	{
		commands->is_built = 1;
		commands->is_built_parent = 1;
	}
	else
		commands->is_built = 0;
}

void	start_exec(t_command *commands, t_infos *infos)
{
	if_builtins(commands);
	if (commands->is_built && !commands->next)
	{
		printf("Builtins\n");
		exec_built(infos, commands);
		return ;
	}
	return;
}