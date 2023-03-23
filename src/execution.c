#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#define CHILD 0

void	execute_cmd(char *argv[], char *envp[])
{
	char	*path;
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
		printf("fork Error\n");
	if (pid == CHILD)
	{
		path = path_creation(argv[0]);
		if (path)
			execve(path, argv, envp);
		printf("ERROR\n");
		return ;
	}
	waitpid(pid, NULL, 0);
}