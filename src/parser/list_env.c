#include "minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

void	ft_free_lst(t_node *head)
{
	t_node	*next;
	t_node	*current;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->data);
		free(current);
		current = next;
	}
}

t_node	*create_node(char *str)
{
	char	**env;
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	env = ft_split(str, '=');
	if (!env)
		return (free(new_node), NULL);
	new_node->name = ft_strdup(env[0]);
	new_node->data = ft_strdup(env[1]);
	ft_2dfree(env);
	if (!new_node->data)
		return (NULL);
	new_node->next = NULL;
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
