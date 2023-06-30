#include <minishell.h>

void	free_infos(t_infos *infos)
{
	t_node	*node;
	t_node	*previous;

	free(infos->pwd);
	node = infos->head;
	while (node)
	{
		previous = node;
		node = node->next;
		free(previous->name);
		free(previous->data);
	}
}
