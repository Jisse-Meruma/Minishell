#include "minishell.h"

t_token	tokenizer(char *token)
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

int	fill_struct(t_lexer *node, t_command *command, const t_parse_meta *meta)
{
	t_token	token;
	char	**arguments;

	while (node != NULL)
	{
		if (ft_ismeta(node->argument[0]))
		{
			if (node->next == NULL || ft_ismeta(node->next->argument[0]))
				return (ERROR);
			token = tokenizer(node->argument);
			if (meta[token](node->next, command, token))
				return (ERROR);
			if (tokenizer(node->argument) == PIPE)
				break ;
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

	node = *lexer;
	command->cmd_argv = ft_calloc(1, sizeof(char *));
	if (!(command->cmd_argv))
		return (ERROR);
	if (fill_struct(node, command, parse_meta))
		return (ERROR);
	return (SUCCES);
}
