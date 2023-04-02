#include "minishell.h"



int	pipe_parse(t_lexer *lexer, t_command *command)
{

}

int	here_parse(t_lexer *lexer, t_command *command)
{
	command->redirects.lst_heredoc = malloc(sizeof(t_lst_redirects));
	if (!(command->redirects.lst_heredoc))
		return (ERROR);
	command->redirects.lst_heredoc->filename = lexer->argument;
	command->redirects.lst_heredoc->next = NULL;
	
}

int	stdinn_parse(t_lexer *lexer, t_command *command)
{
	
}

int	stdout_parse(t_lexer *lexer, t_command *command)
{
	
}

int	append_parse(t_lexer *lexer, t_command *command)
{
	
}

int	parse_struct_command(t_lexer **lexer)
{
	const t_parse_meta	parse_meta[128] = {
	[PIPE] = pipe_parse,
	[HERE_DOC] = here_parse,
	[STDINN_FILE] = stdinn_parse,
	[STDOUT_FILE] = stdout_parse,
	[APPEND_FILE] = append_parse,
	};
	t_lexer				*node;

	node = *lexer;

	while (node->next != NULL)
	{
		if (ft_ismeta(node->argument[0]))
		{
			if(node->next != NULL && ft_ismeta(node->next->argument[0]))
				return (ERROR);
			if ()
		}
		node = node->next;
	}
}