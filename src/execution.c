#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>
#define CHILD 0

void	execute_cmd(char *argv[], char *envp[], t_infos *infos)
{
	char	*path;
	
	infos->pid = fork();
	// signal_cmd(infos);
	if (infos->pid == -1)
		printf("fork Error\n");
	//printf("%d\n", infos->pid);
	if (infos->pid == CHILD)
	{
		path = path_creation(argv[0]);
		if (path)
			execve(path, argv, envp);
		printf("%s\n", strerror(errno));
		return ;
	}
	waitpid(infos->pid, NULL, 0);
}