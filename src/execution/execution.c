#include "minishell.h"
#include <fcntl.h>

void	exec_cmd_child(t_command *cmd, t_infos *infos)
{
	char	*path;

	if (cmd->order == LAST_CMD || cmd->order == ONE_CMD)
		close(infos->pipes[1]);
	dup_all(cmd, infos, 1);
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
			print_error(cmd->cmd_argv[0], strerror(errno));
		}
		if (errno == 13)
			g_glo.error = 126;
		else
			g_glo.error = 127;
	}
	exit(g_glo.error);
}

int	child_birth(t_command *cmd, t_infos *infos, int id)
{
	while (cmd && id != 0)
	{
		if (cmd->order <= 1)
			infos->read_fd = -2;
		else
			infos->read_fd = infos->pipes[0];
		if (cmd->order != LAST_CMD)
		{
			if (pipe(infos->pipes) == -1)
				ret_error("Pipe Error", 2, 1);
		}
		id = fork();
		if (id == -1)
			ret_error("Fork Error", 2, 1);
		if (id != 0)
		{
			close(infos->pipes[1]);
			cmd = cmd->next;
		}
	}
	if (id == 0)
		exec_cmd_child(cmd, infos);
	return (id);
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

void	wait_exec(int id, int32_t status)
{
	waitpid(id, &status, 0);
	if (WIFEXITED(status))
		g_glo.error = WEXITSTATUS(status);
	while (wait(NULL) != -1)
		;
	dup2(0, STDIN_FILENO);
	dup2(1, STDOUT_FILENO);
	return ;
}

void	start_exec(t_command *cmd, t_infos *infos)
{
	int		id;
	int32_t	status;
	int		origin;
	int		dup_err;

	id = 1;
	fill_blt_cmdnb(cmd);
	if ((cmd->next == NULL) && (cmd->cmd_is_blt > 1))
	{
		origin = dup(STDOUT_FILENO);
		dup_err = dup_all(cmd, infos, 0);
		if (!dup_err)
			exec_built(infos, cmd);
		if (infos->write_fd)
		{
			close(infos->write_fd);
			dup2(origin, STDOUT_FILENO);
			close(origin);
		}
		return ;
	}
	id = child_birth(cmd, infos, id);
	wait_exec(id, status);
}
