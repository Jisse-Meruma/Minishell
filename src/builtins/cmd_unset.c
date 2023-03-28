#include "minishell.h"

void    freenode(t_node *node)
{
    free(node->data);
    free(node->name);
    free(node);
}

void	cmd_unset(t_infos *infos, char *node)
{
	t_node *current;
    t_node *next;

    current = infos->head;
    next = current->next;
    while (next != NULL) 
    {
        if (!compare(next->name, node))
        {
            current->next = next->next;
            printf("Unset cmd %s\n", node);
            freenode(next);
            return ;
        }
        next = next->next;
        current = current->next;
    }
}
