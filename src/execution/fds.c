/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fds.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 16:26:07 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/21 17:12:15 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#define FILE 1
#define NO_FILE 0

void	parent_closing(t_infos *infos, int write_fd)
{
	close(infos->read_fd);
	close(write_fd);
}

bool	dup_read(t_command *command, t_infos *infos, int check)
{
	if (check == FILE || command->order > 1)
	{
		if (dup2(infos->read_fd, STDIN_FILENO) == -1)
			return (close(infos->read_fd), false);
		close(infos->read_fd);
	}
	return (true);
}

bool	dup_write(t_command *command, t_infos *infos, int check)
{
	if (check == FILE)
	{
		if (dup2(infos->write_fd, STDOUT_FILENO) == -1)
			return (close(infos->write_fd), false);
		close(infos->write_fd);
		close(infos->pipes[1]);
	}
	else if (command->order != LAST_CMD && command->order != ONE_CMD)
	{
		if (dup2(infos->pipes[1], STDOUT_FILENO) == -1)
			return (close(infos->pipes[1]), false);
		close(infos->pipes[1]);
	}
	return (true);
}

int	check_read_priority(t_command *command)
{
	int				priority;
	t_lst_redirects	*redirect;

	priority = 0;
	redirect = command->lst_redirects;
	while (redirect)
	{
		if (redirect->token == HERE_DOC)
			priority = 1;
		if (redirect->token == STDINN_FILE)
			priority = 2;
		redirect = redirect->next;
	}
	return (priority);
}

int	minishell_continue(t_lst_redirects **redi, bool choice)
{
	if (choice == true)
		*redi = (*redi)->next;
	return (choice);
}
