#include "minishell.h"

char	**parser(char *line)
{
	int			i;
	char		**argv;
	t_lexer		*lexer;
	t_command	*command;

	i = 0;
	lexer = NULL;
	argv = ft_command_split(line);
	argv = remove_quotes(argv);
	if (ft_lexer(&lexer, line))
		printf("PARSING ERROR\n");
	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		printf("Malloc Allocation\n");
	if (parse_struct_command(&lexer, command))
		printf("struct parsing ERROR\n");
	while (lexer != NULL)
	{
		printf("[%d]-[%s]\n", i, lexer->argument);
		lexer = lexer->next;
		i++;
	}
	return (argv);
}
