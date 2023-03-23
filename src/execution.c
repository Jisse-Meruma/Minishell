#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#define CHILD 0

int glopid;

void	f_sig(int sig)
{
	kill(glopid, SIGKILL);
}

void	signall(int pid)
{
	if (pid != CHILD)
	{
		glopid = pid;
		signal(SIGINT, f_sig);
	}
}

void	execute_cmd(char *argv[], char *envp[])
{
	char	*path;
	pid_t	pid;
	
	pid = fork();
	if (pid == -1)
		printf("fork Error\n");
	signall(pid);
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