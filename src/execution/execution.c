#include "minishell.h"
# include <fcntl.h>
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


void	exec_cmd_child(t_command *commands, t_infos *infos)
{
	char *path;

	//dup_in_out(commands, infos);
	path = path_creation(infos, commands->cmd_argv[0]);
	if (path)
		execve(path, commands->cmd_argv, get_envp(infos));
	printf("%s\n", strerror(errno));
	exit(0);
}


int	child_birth(t_command *commands, t_infos *infos, int id)
{
	while (commands && id != 0)
	{
		if (commands->order <= 1)
			commands->read_fd = commands->pipes[0];
		if (pipe(commands->pipes) == -1)
			ret_error("Pipe Error", 2, 1);
		id = fork();
		if (id == -1)
			ret_error("Fork Error", 2, 1);
		if (id != 0)
			commands = commands->next;
	}
	if (id == 0)
		exec_cmd_child(commands, infos);
	// close(commands->pipes[1]);
	return (id);
}

void	fill_blt_cmdnb(t_command *commands)
{
	if_builtins(commands);
	if (commands->next == NULL)
	{
		commands->order = ONE_CMD;
		return;
	}
	commands->order = FIRST_CMD;
	commands = commands->next;
	while (commands)
	{
		if_builtins(commands);
		if (commands->next == NULL)
			commands->order = LAST_CMD;
		else
			commands->order = CMD;
		commands = commands->next;
	}
}

void	start_exec(t_command *commands, t_infos *infos)
{
	int id;
	int32_t	status;

	id = 1;
	fill_blt_cmdnb(commands);
	if ((commands->next == NULL) && (commands->cmd_is_blt != NOT_BUILT))
		return (exec_built(infos, commands));
	id = child_birth(commands, infos, id);
	waitpid(id, &status, 0);
	// need explanation on the wait below
	while (wait(NULL) != -1)
		;
	return ;
}

// int	get_cmd_nb(t_command *commands)
// {
// 	int i;

// 	i = 0;
// 	while (commands != NULL)
// 	{
// 		++i;
// 		commands = commands->next;
// 	}
// 	return (i);
// }
