#include "minishell.h"
# include <fcntl.h>
// < redirect input
// > redirect output
// << heredoc
// >> append mode

// would be nice calling the cmd formated
void	exec_built(t_infos *infos, t_command *cmd)
{
	if (!compare(cmd->cmd_argv[0], "pwd"))
		cmd_pwd(infos);
	else if (!compare(cmd->cmd_argv[0], "echo"))
		cmd_echo(infos, cmd);
	else if (!compare(cmd->cmd_argv[0], "env"))
		cmd_env(infos, cmd);
	else if (!compare(cmd->cmd_argv[0], "getenv"))
		cmd_get_env(infos, cmd->cmd_argv[1]);
	else if (!compare(cmd->cmd_argv[0], "exit"))
		cmd_exit(infos, cmd->cmd_argv);
	else if (!compare(cmd->cmd_argv[0], "cd"))
		cmd_cd(infos, cmd->cmd_argv[1]);
	else if (!compare(cmd->cmd_argv[0], "unset"))
		cmd_unset(infos, cmd);
	else if (!compare(cmd->cmd_argv[0], "export"))
		cmd_export(infos, cmd);
	else
		printf("not a builtins , why am I printing ????\n");
}

void	if_builtins(t_command *cmd)
{
	if (!ft_strncmp("cd", cmd->cmd_argv[0], 3) || \
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

void	exec_cmd_child(t_command *cmd, t_infos *infos)
{
	char	*path;

	if (cmd->order == LAST_CMD || cmd->order == ONE_CMD)
		close(infos->pipes[1]);
	dup_in_out(cmd, infos);
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
			printf("bash: %s: %s\n",cmd->cmd_argv[0], strerror(errno));
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

void	start_exec(t_command *cmd, t_infos *infos)
{
	int		id;
	int32_t	status;

	id = 1;
	fill_blt_cmdnb(cmd);
	if ((cmd->next == NULL) && (cmd->cmd_is_blt != NOT_BUILT))
		return (exec_built(infos, cmd));
	id = child_birth(cmd, infos, id);
	waitpid(id, &status, 0);
	if (WIFEXITED(status))
		g_glo.error = WEXITSTATUS(status);
	while (wait(NULL) != -1)
		;
	dup2(0, STDIN_FILENO);
	dup2(1, STDOUT_FILENO);
	return ;
}
