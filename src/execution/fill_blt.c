/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_blt.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmeruma <jmeruma@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:13:52 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/28 14:46:58 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#define FILE 1
#define NO_FILE 0

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

void	ft_read(t_command *cmd, t_infos *infos)
{
	if (cmd->order <= FIRST_CMD)
		infos->read_fd = -2;
	else
		infos->read_fd = infos->pipes[0];
}

bool	blt_dup_redirects(t_command *cmd, t_infos *infos)
{
	int	priority;
	int	check_read;
	int	check_write;

	check_read = NO_FILE;
	check_write = NO_FILE;
	priority = check_read_priority(cmd);
	if (priority != 0)
	{
		if (!start_heredoc(cmd, infos, &check_read, priority))
			return (false);
		if (!start_read(cmd, infos, &check_read, priority))
			return (false);
	}
	if (!start_write(cmd, infos, &check_write))
		return (false);
	if (infos->read_fd > 0)
		close(infos->read_fd);
	if (!dup_write(cmd, infos, check_write))
		return (false);
	return (true);
}
