#include "minishell.h"



void	printing(t_command *command)
{
	int				i;
	t_lst_redirects	*redirect;

	i = 1;
	while (command)
	{
		printf("/----------------------------\\\n");
		printf("CMD = %s\n", command->cmd_argv[0]);
		printf("ARG = ");
		while (command->cmd_argv[i])
		{
			printf("%s, ", command->cmd_argv[i]);
			i++;
		}
		printf("\n");
		printf("stdin redirect = ");
		redirect = command->lst_redirects;
		while (redirect)
		{
			if (redirect->token == STDINN_FILE)
				printf("%s, ", redirect->filename);
			redirect = redirect->next;
		}
		printf("\n");
		printf("stdout redirect = ");
		redirect = command->lst_redirects;
		while (redirect)
		{
			if (redirect->token == STDOUT_FILE)
				printf("%s, ", redirect->filename);
			redirect = redirect->next;
		}
		printf("\n");
		printf("append redirect = ");
		redirect = command->lst_redirects;
		while (redirect)
		{
			if (redirect->token == APPEND_FILE)
				printf("%s, ", redirect->filename);
			redirect = redirect->next;
		}
		printf("\n");
		printf("here_doc redirect = ");
		redirect = command->lst_redirects;
		while (redirect)
		{
			if (redirect->token == HERE_DOC)
			{
				printf("%s, ", redirect->filename);
				//here_doc(redirect->filename);
			}
			redirect = redirect->next;
		}
		printf("\n");
		printf("/----------------------------\\\n");
		command = command->next;
		i = 1;
	}
}

t_command	*parser(char *line, t_infos *infos)
{
	t_lexer		*lexer;
	t_command	*command;

	lexer = NULL;
	if (*line == '\0')
		return (NULL);
	if (ft_lexer(&lexer, line))
		return (NULL);
	tokenizer(&lexer);
	if (expanding(&lexer, infos))
		return (lexer_free(&lexer), NULL);
	remove_quotes(&lexer);
	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (lexer_free(&lexer), NULL);
	if (parse_struct_command(&lexer, command))
		return (lexer_free(&lexer), NULL);
	lexer_free(&lexer);
	return (command);
}
