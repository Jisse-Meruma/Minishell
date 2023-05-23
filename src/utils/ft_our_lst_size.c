#include "minishell.h"

int	ft_our_lst_size(t_node *lst)
{
	int		count;
	t_node	*current;

	count = 0;
	current = lst;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}
