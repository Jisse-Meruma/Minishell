/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_struc.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:11:28 by mbernede      #+#    #+#                 */
/*   Updated: 2023/08/31 13:11:29 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_infos(t_infos *infos)
{
	t_node	*node;
	t_node	*previous;

	free(infos->pwd);
	node = infos->head;
	while (node)
	{
		previous = node;
		node = node->next;
		free(previous->name);
		free(previous->data);
		free(previous);
	}
}
