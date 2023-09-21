/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_blt.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmeruma <jmeruma@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:13:52 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/21 12:48:22 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

//just filling everything before the exec, good nothing to change

void	exec_built(t_infos *infos, t_command *cmd)
{
	if (!cmd->cmd_argv[0])
		return ;
	if (!compare(cmd->cmd_argv[0], "pwd"))
		cmd_pwd(infos);
	else if (!compare(cmd->cmd_argv[0], "echo"))
		cmd_echo(cmd, infos);
	else if (!compare(cmd->cmd_argv[0], "env"))
		cmd_env(infos);
	else if (!compare(cmd->cmd_argv[0], "getenv"))
		cmd_get_env(infos, cmd->cmd_argv[1]);
	else if (!compare(cmd->cmd_argv[0], "exit"))
		cmd_exit(infos, cmd->cmd_argv);
	else if (!compare(cmd->cmd_argv[0], "cd"))
		cmd_cd(infos, cmd->cmd_argv);
	else if (!compare(cmd->cmd_argv[0], "unset"))
		cmd_unset(infos, cmd);
	else if (!compare(cmd->cmd_argv[0], "export"))
		cmd_export(infos, cmd);
	else
		return ;
}

void	if_builtins(t_command *cmd)
{
	if (!cmd->cmd_argv[0])
		cmd->cmd_is_blt = NOCMD;
	else if (!ft_strncmp("cd", cmd->cmd_argv[0], 3) || \
	!ft_strncmp("exit", cmd->cmd_argv[0], 5) || \
	!ft_strncmp("export", cmd->cmd_argv[0], 7) || \
	!ft_strncmp("unset", cmd->cmd_argv[0], 6))
		cmd->cmd_is_blt = BUILT_PARENT;
	else if (!ft_strncmp("echo", cmd->cmd_argv[0], 5) || \
	!ft_strncmp("env", cmd->cmd_argv[0], 4) || \
	!ft_strncmp("getenv", cmd->cmd_argv[0], 7) || \
	!ft_strncmp("pwd", cmd->cmd_argv[0], 4))
		cmd->cmd_is_blt = BUILT;
	else
		cmd->cmd_is_blt = NOT_BUILT;
}

void	fill_blt_cmdnb(t_command *cmd)
{
	if_builtins(cmd);
	if (cmd->next == NULL)
	{
		cmd->order = ONE_CMD;
		return ;
	}
	cmd->order = FIRST_CMD;
	cmd = cmd->next;
	while (cmd)
	{
		if_builtins(cmd);
		if (cmd->next == NULL)
			cmd->order = LAST_CMD;
		else
			cmd->order = CMD;
		cmd = cmd->next;
	}
}
