#include "minishell.h"
#include <fcntl.h>

bool	exec_heredoc(char *end_of_file, t_infos *infos, int *fd)
{
	*fd = here_doc(end_of_file, infos);
	if (*fd == -1)
		return (false);
	return (true);
}

bool	start_heredoc(t_command *command, t_infos *infos, int *fd)
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
		redirect = redirect->next;
	}
	*fd = file_disciptor;
	return (true);
}

bool	start_read(t_command *command, t_infos *infos, int *fd)
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
		if (file_disciptor == -2 && command->order <= 1)
			close(infos->read_fd);
		file_disciptor = open(redirect->filename, O_RDONLY);
		if (file_disciptor == -1)
			return (false);
		redirect = redirect->next;
	}
	*fd = file_disciptor;
	return (true);
}

bool	start_write(t_command *command, t_infos *infos, int *fd)
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
		if (file_disciptor == -2 && command->order <= 1)
			close(infos->read_fd);
		if (redirect->token == STDOUT_FILE)
			file_disciptor = open(redirect->filename, O_WRONLY | O_CREAT | O_TRUNC, 0000644);
		else if (redirect->token == APPEND_FILE)
			file_disciptor = open(redirect->filename, O_WRONLY | O_APPEND | O_CREAT, 0000644);
		if (file_disciptor == -1)
			return (false);
		redirect = redirect->next;
	}
	*fd = file_disciptor;
	return (true);
}

//return true just for the makefile
bool dup_redirects(t_command *command, t_infos *infos)
{
	int				fd;
	t_lst_redirects	*redirect;

	if (!start_heredoc(command, infos, &infos->read_fd))
		return (false);
	if (!start_read(command, infos, &infos->read_fd))
		return (false);
	if (!start_write(command, infos, &infos->write_fd))

	return (true);
}
