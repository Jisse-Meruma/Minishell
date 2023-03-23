#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char *line;

	line = readline("Minishell$ ");
	while (line)
	{
		add_history(line);
		argv = ft_split(line, ' ');
		//call a if statement now to check for builtins cmds
		ifcmd(argv, envp);
		//execute_cmd(argv, envp);
		ft_2dfree(argv);		
		free(line);
		line = readline("Minishell$ ");
	}
	return (0);
}