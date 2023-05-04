#include "minishell.h"

// print the add var such as var=value as input
//execution is export A=VALUE

void	show_declare(t_infos *infos, int fd)
{
	t_node	*current;

	current = infos->head;
	while (current != NULL)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(current->name, fd);
		if (current->type != EMPTY)
		{
			ft_putstr_fd("=", fd);
			ft_putstr_fd("\"", fd);
			if (current->type == FULL)
				ft_putstr_fd(current->data, fd);
			ft_putstr_fd("\"", fd);
		}
		write(1, "\n", 1);
		current = current->next;
	}
}

void	cmd_export(t_infos *infos, char *str)
{
	t_node	*current;
	t_node	*new_node;
	char	**function;

	g_glo.error = 0;
	if (!str)
		return(show_declare(infos, 1));
	new_node = (t_node *) malloc(sizeof(t_node));
	if (!new_node)
		void_ret_error("Malloc fail", 2);
	function = ft_split(str, '=');
	if (!function)
		return (free(new_node));
	if ((ft_2d_arrlen(function) == 1) && ft_strchr(str, '='))
		new_node->type = NO_VALUE;
	else if ((ft_2d_arrlen(function) == 1) && !ft_strchr(str, '='))
		new_node->type = EMPTY;
	else
		new_node->type = FULL;
	new_node->name = function[0];
	if ((ft_2d_arrlen(function) > 1))
		new_node->data = function[1];
	new_node->next = NULL;
	current = infos->head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}
