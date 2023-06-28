#include "minishell.h"

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
		return (not_valid_id(arg, "unset"));
	current = infos->head;
	next = current->next;
	if (!compare(current->name, arg))
	{
		infos->head = current->next;
		freenode(current);
		return ;
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
	g_glo.error = 0;
	if (!cmd->cmd_argv[arg])
		return ;
	while (cmd->cmd_argv[arg])
	{
		exec_unset(infos, cmd->cmd_argv[arg]);
		++arg;
	}
}
