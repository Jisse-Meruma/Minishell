/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:45:09 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/22 12:51:56 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	node_type(char **function, t_node *new_node, char *str)
{
	if ((ft_2d_arrlen(function) == 1) && !ft_strchr(str, '='))
		new_node->type = EMPTY;
	else if ((ft_2d_arrlen(function) == 1) && ft_strchr(str, '='))
		new_node->type = NO_VALUE;
	else
		new_node->type = FULL;
}

void	create_node_export(t_node *new, char **function, \
t_infos *infos, t_node *current)
{
	new->name = function[0];
	if ((ft_2d_arrlen(function) > 1))
		new->data = function[1];
	else
		new->data = NULL;
	new->next = NULL;
	current = infos->head;
	if (current == NULL)
		infos->head = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

void	change_env_type(t_infos *infos, t_env_data type, char *env_name)
{
	t_node	*current;

	current = infos->head;
	while (current != NULL)
	{
		if (!ft_strncmp(env_name, current->name, ft_strlen(env_name)))
		{
			current->type = type;
			return ;
		}
		current = current->next;
	}
}

void	exec_export(t_infos *infos, char *str)
{
	t_node	*new_node;
	char	**function;

	if (!check_valid_id(str))
		return (not_valid_id(str, "export", infos));
	new_node = (t_node *) malloc(sizeof(t_node));
	if (!new_node)
		return (ft_free_lst(infos->head), exit_error("Malloc fail", 2, infos));
	function = ft_split_first(str, '=');
	if (!function)
	{
		free(new_node);
		return (ft_free_lst(infos->head), exit_error("Malloc fail", 2, infos));
	}
	node_type(function, new_node, str);
	if (cmd_check_env_exist(infos, function[0]))
	{
		if (new_node->type > 0)
			change_env_type(infos, new_node->type, function[0]);
		change_env_data(infos, function[0], function[1]);
		ft_2dfree(function);
		free(new_node);
	}
	else
		create_node_export(new_node, function, infos, NULL);
}

void	cmd_export(t_infos *infos, t_command *cmd)
{
	int	arg;

	arg = 1;
	infos->error = 0;
	if (!cmd->cmd_argv[arg])
		return (show_declare(infos, 1));
	while (cmd->cmd_argv[arg])
	{
		exec_export(infos, cmd->cmd_argv[arg]);
		++arg;
	}
}
