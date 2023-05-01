#include "minishell.h"

t_lexer	*lexer_lstlast(t_lexer *lst)
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
	node = lexer_lstlast(*lst);
	node->next = new;
}

int	lexer_node(t_lexer **lst, char *line, int start, int len)
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

t_lst_redirects	*parse_lstlast(t_lst_redirects *lst)
{
	t_lst_redirects	*current;

	if (lst == NULL)
		return (NULL);
	if (lst->next == NULL)
		return (lst);
	current = lst;
	while (current->next != NULL)
		current = current->next;
	return (current);
}

void	parse_lstadd_back(t_lst_redirects **lst, t_lst_redirects *new)
{
	t_lst_redirects	*node;

	node = *lst;
	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	node = parse_lstlast(*lst);
	node->next = new;
}
