#include "minishell.h"

int	pipe_parse(t_lexer *lexer, t_command *command, t_token token)
{
	(void)token;
	command->next = ft_calloc(1, sizeof(t_command));
	if (!(command->next))
		return (ERROR);
	if (parse_struct_command(&lexer, command->next))
		return (ERROR);
	return (SUCCES);
}

int	here_parse(t_lexer *lexer, t_command *command, t_token token)
{
	t_lst_redirects	*here_doc;

	here_doc = malloc(sizeof(t_lst_redirects));
	if (!here_doc)
		return (ERROR);
	here_doc->token = token;
	here_doc->filename = ft_strdup(lexer->argument);
	if (!here_doc->filename)
		return (ERROR);
	here_doc->next = NULL;
	parse_lstadd_back(&(command->redirects.lst_redirect_read), here_doc);
	return (SUCCES);
}

int	stdinn_parse(t_lexer *lexer, t_command *command, t_token token)
{
	t_lst_redirects	*stdinn_file;

	stdinn_file = malloc(sizeof(t_lst_redirects));
	if (!stdinn_file)
		return (ERROR);
	stdinn_file->token = token;
	stdinn_file->filename = ft_strdup(lexer->argument);
	if (!stdinn_file->filename)
		return (ERROR);
	stdinn_file->next = NULL;
	parse_lstadd_back(&(command->redirects.lst_redirect_read), stdinn_file);
	return (SUCCES);
}

int	stdout_parse(t_lexer *lexer, t_command *command, t_token token)
{
	t_lst_redirects	*stdout_file;

	stdout_file = malloc(sizeof(t_lst_redirects));
	if (!stdout_file)
		return (ERROR);
	stdout_file->token = token;
	stdout_file->filename = ft_strdup(lexer->argument);
	if (!stdout_file->filename)
		return (ERROR);
	stdout_file->next = NULL;
	parse_lstadd_back(&(command->redirects.lst_redirect_write), stdout_file);
	return (SUCCES);
}

int	append_parse(t_lexer *lexer, t_command *command, t_token token)
{
	t_lst_redirects	*append;

	append = malloc(sizeof(t_lst_redirects));
	if (!append)
		return (ERROR);
	append->token = token;
	append->filename = ft_strdup(lexer->argument);
	if (!append->filename)
		return (ERROR);
	append->next = NULL;
	parse_lstadd_back(&(command->redirects.lst_redirect_write), append);
	return (SUCCES);
}
