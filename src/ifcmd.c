#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	ifcmd(char *argv[], char *envp[])
{
	char	*path;
	pid_t	pid;

	if (!compare(argv[0], "pwd"))
		cmd_pwd();
	else if (!compare(argv[0], "env"))
		cmd_env(argv, envp);
	else
		execute_cmd(argv, envp);
}