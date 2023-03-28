#include "minishell.h"

char	**parser(char *line)
{
	int		i;
	char	**argv;

	i = 0;
	argv = ft_command_split(line);

	
	argv = remove_quotes(argv);
	while (argv[i] != NULL)
	{
		printf("[%d], [%s]\n", i, argv[i]);
		i++;
	}
	return (argv);
}
