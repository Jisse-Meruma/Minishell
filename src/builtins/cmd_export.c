#include "minishell.h"

// print the add var such as var=value as input
void	cmd_export(t_infos *infos, char *str)
{
    t_node *current;
    t_node *new_node;
    char **function;

    new_node = (t_node*) malloc(sizeof(t_node));
    if (!new_node)
        return ;
    function = ft_split(str, '=');
    if (!function)
        return (free(new_node));
    new_node->name = function[0];
    new_node->data = function[1];
    new_node->next = NULL;
    ft_2d_arrlen(function);
    current = infos->head;
    while (current->next != NULL) 
        current = current->next;
    current->next = new_node;
}