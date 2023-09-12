#include "minishell.h"
#include <fcntl.h>
#define FILE 1
#define NO_FILE 0

int	check_read_priority(t_command *command)
{
	int	priority;
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

bool	exec_heredoc(char *end_of_file, t_infos *infos, int *fd)
{
	*fd = here_doc(end_of_file, infos);
	if (*fd == -1)
		return (false);
	return (true);
}

bool	start_heredoc(t_command *command, t_infos *infos, int *check, int priority)
{
	int				file_disciptor;
	t_lst_redirects	*redirect;

	file_disciptor = -2;
	redirect = command->lst_redirects;
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
	if (command->order > 1 && *check == FILE)
		close(infos->read_fd);
	if (priority != 1)
		return (close(file_disciptor), true);
	infos->read_fd = file_disciptor;
	return (true);
}

bool	start_read(t_command *command, t_infos *infos, int *check, int priority)
{
	int				file_disciptor;
	t_lst_redirects	*redirect;

	file_disciptor = -2;
	redirect = command->lst_redirects;
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
	if (command->order <= 1 && *check == FILE && priority == 2)
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
		//next line is impossible why is there this line ?
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

//return true just for the makefile
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
