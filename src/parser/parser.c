#include "minishell.h"

char	**parser(char *line)
{
	int		i;
	char	**argv;
	t_lexer *lexer;

	i = 0;
	lexer = NULL;
	argv = ft_command_split(line);
	argv = remove_quotes(argv);
	if (ft_lexer(&lexer, line))
		printf("PARSING ERROR\n");
	
	while (lexer != NULL)
	{
		printf("[%d]-[%s]\n", i, lexer->argument);
		lexer = lexer->next;
		i++;
	}
	return (argv);
}
