/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmeruma <jmeruma@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:13:50 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/29 12:32:18 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void	exec_cmd_child(t_command *cmd, t_infos *infos)
{
	char	*path;

	if (cmd->order != LAST_CMD && cmd->order != ONE_CMD)
		close(infos->pipes[0]);
	mainsignal(3);
	if (!dup_redirects(cmd, infos))
		exit(EXIT_FAILURE);
	if (cmd->cmd_is_blt != NOT_BUILT)
		exec_built(infos, cmd);
	else
	{
		if (cmd->cmd_argv[0][0] != '.')
			path = path_creation(infos, cmd->cmd_argv[0]);
		else
			path = cmd->cmd_argv[0];
		if (path)
		{
			execve(path, cmd->cmd_argv, get_envp(infos));
			print_error(cmd->cmd_argv[0], strerror(errno), infos);
			set_error(infos, errno);
		}
	}
	exit(infos->error);
}

int	commands(t_command *cmd, t_infos *infos, int id)
{
	while (cmd && id != 0)
	{
		ft_read(cmd, infos);
		if (cmd->order != ONE_CMD && cmd->order != LAST_CMD)
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
	if (status == 2)
	{
		printf("\n");
		infos->error = 130;
	}
	if (status == 131 || status == 3)
	{
		ft_putstr_fd("Quit (core dumped)\n", 2);
		infos->error = 131;
	}
	else if (WIFEXITED(status))
		infos->error = WEXITSTATUS(status);
	while (wait(NULL) != -1)
		;
	return ;
}

void	one_blt(t_command *cmd, t_infos *infos)
{
	int	origin;

	origin = dup(STDOUT_FILENO);
	if (!blt_dup_redirects(cmd, infos))
	{
		infos->error = 1;
		return ;
	}
	exec_built(infos, cmd);
	if (infos->write_fd)
	{
		close(infos->write_fd);
		dup2(origin, STDOUT_FILENO);
		close(origin);
	}
}

void	start_exec(t_command *cmd, t_infos *infos)
{
	int		id;

	id = 1;
	fill_blt_cmdnb(cmd);
	if ((cmd->next == NULL) && (cmd->cmd_is_blt > NOT_BUILT))
		return (one_blt(cmd, infos));
	if (cmd && cmd->cmd_argv[0] && !cmd->cmd_argv[0][0])
		fix_cmd(cmd);
	mainsignal(1);
	id = commands(cmd, infos, id);
	wait_exec(id, infos);
	mainsignal(0);
}
