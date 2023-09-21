/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:55:07 by jmeruma           #+#    #+#             */
/*   Updated: 2023/09/21 11:55:08 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_lst(t_node *head)
{
	t_node	*next;
	t_node	*current;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->data);
		free(current);
		current = next;
	}
}

int	unexpected_token(t_lexer *node)
{
	if (!node)
		return (ERROR);
	write(2, "syntax error near unexpected token `", 36);
	write(2, node->argument, ft_strlen(node->argument));
	write(2, "'\n", 2);
	return (ERROR);
}

int	fill_struct(t_lexer *node, t_command *command, const t_parse_meta *meta)
{
	char	**arguments;

	while (node != NULL)
	{
		if (node->token != TEXT_TOKEN)
		{
			if (node->next == NULL || \
			(node->next->token != TEXT_TOKEN && node->token != PIPE))
				return (unexpected_token(node->next));
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
