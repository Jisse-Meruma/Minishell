#include "minishell.h"

int	parse_struct_command(t_lexer **lexer, t_command *command);

int	pipe_parse(t_lexer *lexer, t_command *command)
{
	printf("GOT IN PIPE\n");
	command->next = ft_calloc(1, sizeof(t_command));
	if (!(command->next))
		return (ERROR);
	parse_struct_command(&lexer, command->next);
	return (SUCCES);
}

int	here_parse(t_lexer *lexer, t_command *command)
{
	t_lst_redirects	*here_doc;

	printf("GOT IN DOC\n");
	here_doc = malloc(sizeof(t_lst_redirects));
	if (!here_doc)
		return (ERROR);
	here_doc->filename = lexer->argument;
	here_doc->next = NULL;
	parse_lstadd_back(&(command->redirects.lst_heredoc), here_doc);
	return (SUCCES);
}

int	stdinn_parse(t_lexer *lexer, t_command *command)
{
	t_lst_redirects	*stdinn_file;

	printf("GOT IN in\n");
	stdinn_file = malloc(sizeof(t_lst_redirects));
	if (!stdinn_file)
		return (ERROR);
	stdinn_file->filename = lexer->argument;
	stdinn_file->next = NULL;
	parse_lstadd_back(&(command->redirects.lst_redirect_inn), stdinn_file);
	return (SUCCES);
}

int	stdout_parse(t_lexer *lexer, t_command *command)
{
		t_lst_redirects	*stdout_file;

	printf("GOT IN out\n");
	stdout_file = malloc(sizeof(t_lst_redirects));
	if (!stdout_file)
		return (ERROR);
	stdout_file->filename = lexer->argument;
	stdout_file->next = NULL;
	parse_lstadd_back(&(command->redirects.lst_redirect_out), stdout_file);
	return (SUCCES);
}

int	append_parse(t_lexer *lexer, t_command *command)
{
		t_lst_redirects	*append;

	append = malloc(sizeof(t_lst_redirects));
	if (!append)
		return (ERROR);
	append->filename = lexer->argument;
	append->next = NULL;
	parse_lstadd_back(&(command->redirects.lst_append), append);
	return (SUCCES);
}

int	tokenizer(char *token)
{
	if (!ft_strncmp(token, "|", 2))
		return (PIPE);
	else if (!ft_strncmp(token, "<", 2))
		return (STDINN_FILE);
	else if (!ft_strncmp(token, ">", 2))
		return (STDOUT_FILE);
	else if (!ft_strncmp(token, ">>", 3))
		return (APPEND_FILE);
	else if (!ft_strncmp(token, "<<", 3))
		return (HERE_DOC);
	return (ERROR);
}

int	parse_struct_command(t_lexer **lexer, t_command *command)
{
	const t_parse_meta	parse_meta[5] = {
	[PIPE] = pipe_parse,
	[HERE_DOC] = here_parse,
	[STDINN_FILE] = stdinn_parse,
	[STDOUT_FILE] = stdout_parse,
	[APPEND_FILE] = append_parse,
	};
	t_lexer				*node;
	char	**arguments;

	node = *lexer;
	command->cmd_argv = ft_calloc(1, sizeof(char *));
	if (!(command->cmd_argv))
		return (ERROR);
	while (node != NULL)
	{
		if (ft_ismeta(node->argument[0]))
		{
			if(node->next == NULL || ft_ismeta(node->next->argument[0]))
				return (ERROR);
			if (parse_meta[tokenizer(node->argument)](node->next, command))
				return (ERROR);
			if (tokenizer(node->argument) == PIPE)
				break;
			node = node->next;
		}
		else
		{
			arguments = command->cmd_argv;
			command->cmd_argv = ft_2d_add(arguments, node->argument);
			ft_2dfree(arguments);
		}
		node = node->next;
	}
	return (SUCCES);
}