/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_envp.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:13:57 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/07 15:27:22 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_str(t_node *current)
{
	char	*str;

	str = ft_strdup(current->name);
	if (!str)
		return (NULL);
	str = ft_strjoin_free(str, "=");
	if (!str)
		return (NULL);
	if (current->data)
		str = ft_strjoin_free(str, current->data);
	return (str);
}

char	**get_envp(t_infos *infos)
{
	t_node	*current;
	char	**envp;
	int		i;
	char	*temp;

	current = infos->head;
	i = 0;
	envp = (char **) malloc((ft_our_lst_size(current) + 1) * sizeof(char *));
	if (!envp)
		return (ret_error("Malloc error", 2, 0), NULL);
	while (current)
	{
		temp = env_str(current);
		envp[i] = temp;
		current = current->next;
		++i;
	}
	envp[i] = NULL;
	return (envp);
}
