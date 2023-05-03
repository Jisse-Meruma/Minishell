#include "minishell.h"

// print the linked list
void	cmd_env(t_infos *infos)
{
	t_node *current;

	current = infos->head;
	while (current != NULL) 
	{
		ft_putstr_fd(current->name, 1);
		write(1, "=", 1);
		if (current->data)
			 ft_putstr_fd(current->data, 1);
		write(1, "\n", 1);
		current = current->next;
	}
}
