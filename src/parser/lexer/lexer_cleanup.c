/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:55:51 by jmeruma           #+#    #+#             */
/*   Updated: 2023/09/21 11:55:52 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lexer_free(t_lexer **lexer)
{
	t_lexer	*node;
	t_lexer	*prev_node;

	node = *lexer;
	while (node)
	{
		prev_node = node;
		free(node->argument);
		node = node->next;
		free(prev_node);
	}
	lexer = NULL;
}
