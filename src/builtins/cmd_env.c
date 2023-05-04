#include "minishell.h"

// print the linked list where value != 0
void	cmd_env(t_infos *infos)
{
	t_node	*current;

	current = infos->head;
	while (current != NULL)
	{
		if (current->type)
		{
			ft_putstr_fd(current->name, 1);
			write(1, "=", 1);
			if (current->type == FULL)
				ft_putstr_fd(current->data, 1);
			write(1, "\n", 1);
		}
		current = current->next;
	}
}
