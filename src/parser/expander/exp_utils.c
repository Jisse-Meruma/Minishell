/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exp_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmeruma <jmeruma@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 11:55:41 by jmeruma       #+#    #+#                 */
/*   Updated: 2023/09/29 11:42:15 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	quote_status(bool quotes)
{
	if (quotes == true)
		quotes = false;
	else
		quotes = true;
	return (quotes);
}

int	skip_single_quote(char *line, int index)
{
	while (line[index] != '\'' && line[index])
		index++;
	return (index);
}

bool	is_redirect(t_token token)
{
	if (token == STDINN_FILE || token == STDOUT_FILE \
		|| token == APPEND_FILE)
		return (true);
	return (false);
}

bool	ambiguous_redir(t_lexer	**lexer, t_lexer *node, char *str)
{
	t_lexer	*prev_node;

	prev_node = *lexer;
	while (prev_node->next && prev_node->next != node)
		prev_node = prev_node->next;
	if (!is_redirect(prev_node->token))
		return (false);
	write(2, "Celeste-shell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": ambiguous redirect\n", 21);
	return (true);
}

int	env_name_lenght(char *line, int index, int i)
{
	while (line[index + i])
	{
		if (line[index + i] == '\"' || line[index + i] == '$'\
				|| line[index + i] == '\'' || ft_isspace(line[index + i]))
			break ;
		i++;
	}
	return (i);
}
