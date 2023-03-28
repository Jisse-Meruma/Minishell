#include "minishell.h"

void	cmd_env(t_infos *infos)
{
    t_node *current;

    current = infos->head;
    while (current != NULL) 
    {
        printf("%s=%s\n",current->name, current->data);
        current = current->next;
    }
}