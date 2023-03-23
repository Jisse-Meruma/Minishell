#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	cmd_env(char *argv[], char *envp[])
{
	char	*env;
	int i;

	i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		write(1, "\n", 1);
		++i;
	}
}