#include "minishell.h"

int	fill_struct(t_lexer *node, t_command *command, const t_parse_meta *meta)
{
	char	**arguments;

	while (node != NULL)
	{
		if (node->token != TEXT_TOKEN)
		{
			if (node->next == NULL || node->next->token != TEXT_TOKEN)
				return (ERROR);
			if (meta[node->token](node->next, command, node->token))
				return (ERROR);
			if (node->token == PIPE)
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
