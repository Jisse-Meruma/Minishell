#include "minishell.h"
#include <fcntl.h>
#define FILE 1
#define NO_FILE 0

bool	exec_heredoc(char *end_of_file, t_infos *infos, int *fd)
{
	*fd = here_doc(end_of_file, infos);
	if (*fd == -1)
		return (false);
	return (true);
}

bool	start_heredoc(t_command *cmd, t_infos *infos, int *check, int priority)
{
	int				file_disciptor;
	t_lst_redirects	*redirect;

	file_disciptor = -2;
	redirect = cmd->lst_redirects;
	while (redirect)
	{
		if (redirect->token != HERE_DOC)
		{
			redirect = redirect->next;
			continue ;
		}
		if (file_disciptor != -2)
			close(file_disciptor);
		if (!exec_heredoc(redirect->filename, infos, &file_disciptor))
			return (false);
		*check = FILE;
		redirect = redirect->next;
	}
	if (cmd->order > 1 && *check == FILE)
		close(infos->read_fd);
	if (priority != 1)
		return (close(file_disciptor), true);
	infos->read_fd = file_disciptor;
	return (true);
}

bool	start_read(t_command *cmd, t_infos *infos, int *check, int priority)
{
	int				file_disciptor;
	t_lst_redirects	*redirect;

	file_disciptor = -2;
	redirect = cmd->lst_redirects;
	while (redirect)
	{
		if (redirect->token != STDINN_FILE)
		{
			redirect = redirect->next;
			continue ;
		}
		if (file_disciptor != -2)
			close(file_disciptor);
		file_disciptor = open(redirect->filename, O_RDONLY);
		if (file_disciptor == -1)
			return (minishell_perror(redirect->filename), false);
		*check = FILE;
		redirect = redirect->next;
	}
	if (cmd->order <= 1 && *check == FILE && priority == 2)
		close(infos->read_fd);
	if (priority != 2)
		return (close(file_disciptor), true);
	infos->read_fd = file_disciptor;
	return (true);
}

bool	start_write(t_command *command, t_infos *infos, int *check)
{
	int				file_disciptor;
	t_lst_redirects	*redirect;

	file_disciptor = -2;
	redirect = command->lst_redirects;
	while (redirect)
	{
		if (redirect->token != APPEND_FILE && redirect->token != STDOUT_FILE)
		{
			redirect = redirect->next;
			continue ;
		}
		if (file_disciptor != -2)
			close(file_disciptor);
		if (redirect->token == STDOUT_FILE)
			file_disciptor = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0000644);
		else if (redirect->token == APPEND_FILE)
			file_disciptor = open(redirect->filename, O_WRONLY | O_APPEND | O_CREAT, 0000644);
		if (file_disciptor == -1)
			return (minishell_perror(redirect->filename), false);
		*check = FILE;
		redirect = redirect->next;
	}
	if (*check == FILE)
		infos->write_fd = file_disciptor;
	return (true);
}

bool dup_redirects(t_command *command, t_infos *infos)
{
	int	priority;
	int	check_read;
	int check_write;
	
	check_read = NO_FILE;
	check_write = NO_FILE;
	priority = check_read_priority(command);
	if (priority != 0)
	{
		if (!start_heredoc(command, infos, &check_read, priority))
			return (false);
		if (!start_read(command, infos, &check_read, priority))
			return (false);
	}
	if (!start_write(command, infos, &check_write))
		return (false);
	if (!dup_read(command, infos, check_read))
		return (false);
	if (!dup_write(command, infos, check_write))
		return (false);
	return (true);
}
