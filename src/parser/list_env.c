/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   list_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmeruma <jmeruma@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 11:55:14 by jmeruma       #+#    #+#                 */
/*   Updated: 2023/09/21 13:22:15 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	ft_free_node(t_node *node)
{
	free(node->name);
	free(node->data);
	free(node);
}

t_node	*create_node(char *str)
{
	char	**env;
	t_node	*new_node;

	new_node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!new_node)
		return (NULL);
	env = ft_split_first(str, '=');
	if (!env)
		return (free(new_node), NULL);
	new_node->name = ft_strdup(env[0]);
	if (!new_node->name)
		return (ft_free_node(new_node), ft_2dfree(env), NULL);
	if (env[1])
		new_node->data = ft_strdup(env[1]);
	else
		new_node->data = ft_strdup("");
	new_node->type = 2;
	ft_2dfree(env);
	if (!new_node->data)
		return (ft_free_node(new_node), NULL);
	return (new_node);
}

int	insert_node(t_node **head, char *str)
{
	t_node	*new_node;
	t_node	*current;

	new_node = create_node(str);
	if (!new_node)
		return (ft_free_lst(*head), 1);
	if (*head == NULL)
	{
		*head = new_node;
		return (0);
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
	return (0);
}

void	print_list(t_node *head)
{
	t_node	*current;

	current = head;
	while (current != NULL)
	{
		printf("%s=%s\n", current->name, current->data);
		current = current->next;
	}
}

int	list_env(char **env, t_infos *infos)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (insert_node(&infos->head, env[i]))
			return (1);
		++i;
	}
	return (0);
}
