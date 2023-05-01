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
		redirect = command->redirects.lst_redirect_read;
		while (redirect)
		{
			if (redirect->token == STDINN_FILE)
				printf("%s, ", redirect->filename);
			redirect = redirect->next;
		}
		printf("\n");
		printf("stdout redirect = ");
		redirect = command->redirects.lst_redirect_write;
		while (redirect)
		{
			if (redirect->token == STDOUT_FILE)
				printf("%s, ", redirect->filename);
			redirect = redirect->next;
		}
		printf("\n");
		printf("append redirect = ");
		redirect = command->redirects.lst_redirect_write;
		while (redirect)
		{
			if (redirect->token == APPEND_FILE)
				printf("%s, ", redirect->filename);
			redirect = redirect->next;
		}
		printf("\n");
		printf("here_doc redirect = ");
		redirect = command->redirects.lst_redirect_read;
		while (redirect)
		{
			if (redirect->token == HERE_DOC)
			{
				printf("%s, ", redirect->filename);
				here_doc(redirect->filename);
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
	int			i;
	t_lexer		*lexer;
	t_command	*command;

	i = 0;
	lexer = NULL;
	if (*line == '\0')
		return (NULL);
	if (ft_lexer(&lexer, line))
	{
		printf("PARSING ERROR\n");
		return (NULL);
	}
	tokenizer(&lexer);
	expanding(&lexer, infos);
	remove_quotes(&lexer);
	command = ft_calloc(1, sizeof(t_command));
	if (!command)
	{
		printf("Malloc Allocation\n");
		return (NULL);
	}
	if (parse_struct_command(&lexer, command))
	{
		printf("struct parsing ERROR\n");
		return (NULL);
	}
	lexer_free(&lexer);
	printing(command);
	return (command);
}
