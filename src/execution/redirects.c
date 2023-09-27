/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirects.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/27 14:31:13 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/27 14:53:32 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#define FILE 1
#define NO_FILE 0

bool	dup_out(t_command *cmd, t_infos *infos, int *fd_write, t_lst_redirects *redi)
{
	if (*fd_write != -2)
		close(*fd_write);
	if (redi->token == STDOUT_FILE)
		*fd_write = open(redi->filename, O_WRONLY | O_CREAT | O_TRUNC, 0000644);
	if (redi->token == APPEND_FILE)
		*fd_write = open(redi->filename, O_WRONLY | O_APPEND | O_CREAT, 0000644);
	if (*fd_write == -1)
		return (minishell_perror(redi->filename), false);
	infos->write_fd = *fd_write;
	return (true);
}

bool	dup_in(t_command *cmd, t_infos *infos, int *fd_read, t_lst_redirects *redi)
{
	if (*fd_read != -2)
		close(*fd_read);
	if (redi->token == STDINN_FILE)
		*fd_read = open(redi->filename, O_RDONLY);
	if (redi->token == HERE_DOC)
	{
		if (!exec_heredoc(redi->filename, infos, &fd_read))
			return (false);
	}
	if (*fd_read == -1)
		return (minishell_perror(redi->filename), false);
	infos->read_fd = *fd_read;
	return (true);
}

bool	dup_redirects2(t_command *cmd, t_infos *infos)
{
	t_lst_redirects	*redi;
	int	fd_read;
	int	fd_write;

	redi = cmd->lst_redirects;
	fd_read = -2;
	fd_write = -2;
	while (redi)
	{
		if (redi->token == STDOUT_FILE || redi->token == APPEND_FILE)
			dup_out(cmd, infos, &fd_write, redi);
		if (redi->token == STDINN_FILE || redi->token == HERE_DOC)
			dup_in(cmd, infos, &fd_read, redi);	
	}
	// if (!start_write(cmd, infos, &check_write))
	// 	return (false);
	// if (!dup_read(cmd, infos, check_read))
	// 	return (false);
	// if (!dup_write(cmd, infos, check_write))
	// 	return (false);
	return (true);
}