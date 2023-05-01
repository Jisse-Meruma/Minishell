/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:52:59 by jmeruma           #+#    #+#             */
/*   Updated: 2023/04/26 12:30:50 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	token(char *token)
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

void	tokenizer(t_lexer **lexer)
{
	t_lexer	*node;

	node = *lexer;
	while (node != NULL)
	{
		if (ft_ismeta(node->argument[0]))
			node->token = token(node->argument);
		else
			node->token = TEXT_TOKEN;
		node = node->next;
	}
}
