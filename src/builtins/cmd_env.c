#include "minishell.h"

// print the linked list
void	cmd_env(t_infos *infos)
{
    t_node *current;

    printf("hello\n");
    current = infos->head;
    while (current != NULL) 
    {
        printf("%s=%s\n",current->name, current->data);
        current = current->next;
    }
}