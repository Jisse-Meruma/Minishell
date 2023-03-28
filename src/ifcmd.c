#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	ifcmd(char *argv[], char *envp[], t_infos *infos)
{
	if (!compare(argv[0], "pwd"))
		cmd_pwd(infos);
	else if (!compare(argv[0], "env"))
		cmd_env(infos);
	else if (!compare(argv[0], "cd"))
		cmd_cd(infos);
	else
		execute_cmd(argv, envp, infos);
}