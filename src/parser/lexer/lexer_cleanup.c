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
