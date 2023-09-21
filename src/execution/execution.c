/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmeruma <jmeruma@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:13:50 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/21 16:26:17 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

void	exec_cmd_child(t_command *cmd, t_infos *infos)
{
	char	*path;

	if (cmd->order == LAST_CMD || cmd->order == ONE_CMD)
		close(infos->pipes[1]);
	if (!dup_redirects(cmd, infos))
		exit(EXIT_FAILURE);
	if (cmd->cmd_is_blt != NOT_BUILT)
		exec_built(infos, cmd);
	else
	{
		if (cmd->cmd_argv[0][0] == '.')
			path = cmd->cmd_argv[0];
		else
			path = path_creation(infos, cmd->cmd_argv[0]);
		if (path)
		{
			execve(path, cmd->cmd_argv, get_envp(infos));
			print_error(cmd->cmd_argv[0], strerror(errno), infos);
		}
		if (errno == 13)
			infos->error = 126;
		else
			infos->error = 127;
	}
	exit(infos->error);
}

int	child_birth(t_command *cmd, t_infos *infos, int id, int ex)
{
	while (cmd && id != 0 && ex)
	{
		if (cmd->order <= 1)
			infos->read_fd = -2;
		else
			infos->read_fd = infos->pipes[0];
		if (cmd->order != LAST_CMD && cmd->order != ONE_CMD)
		{
			if (pipe(infos->pipes) == -1)
				return (ret_error("Pipe Error", 2, 1));
		}
		id = fork();
		if (id == -1)
			return (ret_error("Fork Error", 2, 1));
		if (id == 0)
			exec_cmd_child(cmd, infos);
		if (cmd->order != ONE_CMD && cmd->order != LAST_CMD)
			close(infos->pipes[1]);
		if (infos->read_fd != -2)
			close(infos->read_fd);
		cmd = cmd->next;
	}
	return (id);
}

void	wait_exec(int id, t_infos *infos)
{
	int32_t	status;

	waitpid(id, &status, 0);
	if (WIFEXITED(status))
		infos->error = WEXITSTATUS(status);
	while (wait(NULL) != -1)
		;
	return ;
}

void	one_blt(t_command *cmd, t_infos *infos)
{
	int	origin;

	origin = dup(STDOUT_FILENO);
	if (!dup_redirects(cmd, infos))
		return ;
	exec_built(infos, cmd);
	if (infos->write_fd)
	{
		close(infos->write_fd);
		dup2(origin, STDOUT_FILENO);
		close(origin);
	}
	return ;
}

void	start_exec(t_command *cmd, t_infos *infos)
{
	int		id;
	int		execution;

	id = 1;
	execution = 1;
	fill_blt_cmdnb(cmd);
	if ((cmd->next == NULL) && (cmd->cmd_is_blt > 1))
		return (one_blt(cmd, infos));
	if (cmd && cmd->cmd_argv[0] && !cmd->cmd_argv[0][0])
		fix_cmd(cmd, infos, &execution);
	id = child_birth(cmd, infos, id, execution);
	wait_exec(id, infos);
}
