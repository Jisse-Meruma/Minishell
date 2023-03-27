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
		// parser needs to return a linked_list but for now it return a 2d_array
		argv = parser(line);
		//call a if statement now to check for builtins cmds
		if (ft_2d_arrlen(argv))
			ifcmd(argv, envp);
		ft_2dfree(argv);		
		free(line);
		line = readline("Minishell$ ");
	}
	return (0);
}