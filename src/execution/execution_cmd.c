/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution_cmd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 17:11:22 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/27 18:40:36 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#define FILE 1
#define NO_FILE 0

bool	exec_heredoc(char *end_of_file, t_infos *infos, int *fd)
{
	mainsignal(2);
	*fd = here_doc(end_of_file, infos);
	if (*fd == -1)
		return (false);
	return (true);
}

bool	start_heredoc(t_command *cmd, t_infos *infos, int *check, int priority)
{
	int				fd;
	t_lst_redirects	*redi;

	fd = -2;
	redi = cmd->lst_redirects;
	while (redi)
	{
		if (redi->token != HERE_DOC)
		{
			redi = redi->next;
			continue ;
		}
		if (fd != -2)
			close(fd);
		if (!exec_heredoc(redi->filename, infos, &fd))
			return (false);
		*check = FILE;
		redi = redi->next;
	}
	if (cmd->order > 1 && *check == FILE)
		close(infos->read_fd);
	if (priority != 1)
		return (close(fd), true);
	infos->read_fd = fd;
	return (true);
}

bool	start_read(t_command *cmd, t_infos *infos, int *check, int priority)
{
	int				fd;
	t_lst_redirects	*redi;

	fd = -2;
	redi = cmd->lst_redirects;
	while (redi)
	{
		if (minishell_continue(&redi, redi->token != STDINN_FILE))
			continue ;
		if (fd != -2)
			close(fd);
		fd = open(redi->filename, O_RDONLY);
		if (fd == -1)
			return (minishell_perror(redi->filename), false);
		*check = FILE;
		redi = redi->next;
	}
	if (cmd->order <= 1 && *check == FILE && priority == 2)
		close(infos->read_fd);
	if (priority != 2)
		return (close(fd), true);
	infos->read_fd = fd;
	return (true);
}

bool	start_write(t_command *cmd, t_infos *infos, int *check)
{
	int				fd;
	t_lst_redirects	*redi;

	fd = -2;
	redi = cmd->lst_redirects;
	while (redi)
	{
		if (minishell_continue(&redi, redi->token != APPEND_FILE \
		&& redi->token != STDOUT_FILE))
			continue ;
		if (fd != -2)
			close(fd);
		if (redi->token == STDOUT_FILE)
			fd = open(redi->filename, O_WRONLY | O_CREAT | O_TRUNC, 0000644);
		else if (redi->token == APPEND_FILE)
			fd = open(redi->filename, O_WRONLY | O_APPEND | O_CREAT, 0000644);
		if (fd == -1)
			return (minishell_perror(redi->filename), false);
		*check = FILE;
		redi = redi->next;
	}
	if (*check == FILE)
		infos->write_fd = fd;
	return (true);
}

bool	dup_redirects(t_command *cmd, t_infos *infos)
{
	int	priority;
	int	check_read;
	int	check_write;

	check_read = NO_FILE;
	check_write = NO_FILE;
	priority = check_read_priority(cmd);
	if (priority != 0)
	{
		if (!start_heredoc(cmd, infos, &check_read, priority))
			return (false);
		if (!start_read(cmd, infos, &check_read, priority))
			return (false);
	}
	if (!start_write(cmd, infos, &check_write))
		return (false);
	if (!dup_read(cmd, infos, check_read))
		return (false);
	if (!dup_write(cmd, infos, check_write))
		return (false);
	return (true);
}

bool	blt_dup_redirects(t_command *cmd, t_infos *infos)
{
	int	priority;
	int	check_read;
	int	check_write;

	check_read = NO_FILE;
	check_write = NO_FILE;
	priority = check_read_priority(cmd);
	if (priority != 0)
	{
		if (!start_heredoc(cmd, infos, &check_read, priority))
			return (false);
		if (!start_read(cmd, infos, &check_read, priority))
			return (false);
	}
	if (!start_write(cmd, infos, &check_write))
		return (false);
	close(infos->read_fd);
	if (!dup_write(cmd, infos, check_write))
		return (false);
	return (true);
}