#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	ifcmd(char *argv[], char *envp[], t_infos *infos)
{
	if (!compare(argv[0], "pwd"))
		cmd_pwd(infos);
	else if (!compare(argv[0], "echo"))
		cmd_echo(infos, argv);
	else if (!compare(argv[0], "env"))
		cmd_env(infos);
	else if (!compare(argv[0], "exit"))
		cmd_exit(infos);
	else if (!compare(argv[0], "cd"))
		cmd_cd(infos, argv[1]);
	else if (!compare(argv[0], "unset"))
		cmd_unset(infos, argv[1]);
	else if (!compare(argv[0], "export"))
		cmd_export(infos, argv[1]);
	else
		execute_cmd(argv, envp, infos);
}