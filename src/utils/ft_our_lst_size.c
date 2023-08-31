/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_our_lst_size.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:06:03 by mbernede      #+#    #+#                 */
/*   Updated: 2023/08/31 13:06:04 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_our_lst_size(t_node *lst)
{
	int		count;
	t_node	*current;

	count = 0;
	current = lst;
	while (current != NULL)
	{
		count++;
		current = current->next;
	}
	return (count);
}
