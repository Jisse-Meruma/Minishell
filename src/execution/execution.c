#include "minishell.h"
// < redirect input
// > redirect output
// << heredoc
// >> append mode

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

void	if_builtins(t_command *commands)
{
	if (!ft_strncmp("cd", commands->cmd_argv[0], 3) || \
	!ft_strncmp("exit", commands->cmd_argv[0], 5) || \
	!ft_strncmp("export", commands->cmd_argv[0], 7) || \
	!ft_strncmp("unset", commands->cmd_argv[0], 6))
		commands->cmd_is_blt = BUILT_PARENT;
	else if (!ft_strncmp("echo", commands->cmd_argv[0], 5) || \
	!ft_strncmp("env", commands->cmd_argv[0], 4) || \
	!ft_strncmp("getenv", commands->cmd_argv[0], 7) || \
	!ft_strncmp("pwd", commands->cmd_argv[0], 4))
		commands->cmd_is_blt = BUILT;
	else
		commands->cmd_is_blt = NOT_BUILT;
}

int	get_cmd_nb(t_command *commands)
{
	int i;

	i = 0;
	while (commands != NULL)
	{
		++i;
		commands = commands->next;
	}
	return (i);
}

void	exec_cmd_child(t_command *commands, t_infos *infos, int cmd_nb)
{
	char *path;

	//readfd = getreadfd();
	if (cmd_nb)
		close(commands->read_fd);
	//writefd = getwritefd();
	path = path_creation(infos, commands->cmd_argv[0]);
	if (path)
		execve(path, commands->cmd_argv, get_envp(infos));
	printf("%s\n", strerror(errno));
	exit(0);
}

int	child_birth(t_command *commands, t_infos *infos, int id)
{
	int	cmd_nb;
	// int cmd_nb_max;
	// cmd_nb_max = get_cmd_nb(commands);

	cmd_nb = 0;
	while (commands && id != 0)
	{
		if (cmd_nb != 0)
			commands->read_fd = commands->pipes[0];
		++cmd_nb;
		if (pipe(commands->pipes) == -1)
			ret_error("Pipe Error", 2, 1);
		id = fork();
		if (id == -1)
			ret_error("Fork Error", 2, 1);
		if (id == 0)
			if_builtins(commands);
		if (id != 0)
			commands = commands->next;
	}
	if (id == 0)
		exec_cmd_child(commands, infos, cmd_nb);
	close(commands->pipes[1]);
	return (id);
}

void	start_exec(t_command *commands, t_infos *infos)
{
	int id;
	int32_t	status;

	if_builtins(commands);
	if ((commands->next == NULL) && (commands->cmd_is_blt != NOT_BUILT))
		return (exec_built(infos, commands));
	id = child_birth(commands, infos, id);
	waitpid(id, &status, 0);
	// is it necesarry to use cmd_argv ?
	// if (commands->cmd_argv[0] == NULL)
	// {
	// 	printf("Maybe do something :D/ft_strncmp segfaults when argv[0] = NULL\n");
	// 	return ;
	// }

	//add the ifbuiltins in each cmds
	//if_builtins(commands);
	// if (commands->cmd_is_blt && !commands->next)
	// {
	// 	printf("Execution.c : Builtins\n");
	// 	exec_built(infos, commands);
	// 	return ;
	// }
	return ;
}
