/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_unset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:44:59 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/21 16:32:05 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norm_def(t_node *current, t_node *next, t_infos *infos)
{
	current = infos->head;
	next = current->next;
}

void	freenode(t_node *node)
{
	free(node->data);
	free(node->name);
	free(node);
}

void	exec_unset(t_infos *infos, char *arg)
{
	t_node	*current;
	t_node	*next;

	if (!arg)
		return ;
	if (!arg[0])
		return (not_valid_id(arg, "unset", infos));
	current = infos->head;
	next = current->next;
	if (!compare(current->name, arg))
	{
		infos->head = current->next;
		return (freenode(current));
	}
	while (next != NULL)
	{
		if (!compare(next->name, arg))
		{
			current->next = next->next;
			freenode(next);
			return ;
		}
		next = next->next;
		current = current->next;
	}
}

void	cmd_unset(t_infos *infos, t_command *cmd)
{
	int	arg;

	arg = 1;
	infos->error = 0;
	if (!cmd->cmd_argv[arg])
		return ;
	while (cmd->cmd_argv[arg])
	{
		exec_unset(infos, cmd->cmd_argv[arg]);
		++arg;
	}
}
