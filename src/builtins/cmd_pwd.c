#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	cmd_pwd(void)
{
	char	*envpwd;

	envpwd = getcwd(NULL, 0);
	ft_putstr_fd(envpwd, 1);
	printf("\n");
}