/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_export_d.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:52:50 by mbernede      #+#    #+#                 */
/*   Updated: 2023/08/31 13:52:55 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		write(fd, "\n", 1);
		current = current->next;
	}
}
