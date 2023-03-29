#include "minishell.h"

t_list	*lexer_lstlast(t_lexer *lst)
{
	t_lexer	*current;

	if (lst == NULL)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

void	lexer_lstadd_back(t_lexer **lst, t_lexer *new)
{
	t_lexer	*node;

	node = *lst;
	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	node = ft_lstlast(*lst);
	node->next = new;
}

int	create_node(t_lexer **lst, char *line, int start, int len)
{
	t_lexer	*node;

	node = malloc(sizeof(t_lexer));
	if (!node)
		return (ERROR);
	node->argument = ft_substr(line, start, len);
	if (!node->argument)
		return (ERROR);
	node->next = NULL;
	lexer_lstadd_back(lst, node);
	return (SUCCES);
}
