#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	char	*line;

	line = readline("Minishell$ ");
	while (line)
	{
		i = 0;
		add_history(line);
		argv = ft_command_split(line);
		while (argv[i] != NULL)
		{
			printf("[%d]-[%s]\n", i, argv[i]);
			i++;
		}
		//call a if statement now to check for builtins cmds
		ifcmd(argv, envp);
		execute_cmd(argv, envp);
		ft_2dfree(argv);		
		free(line);
		line = readline("Minishell$ ");
	}
	return (0);
}