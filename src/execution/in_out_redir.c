#include <minishell.h>
#include <fcntl.h>

// check if theres a next redirect of the same type later to only dup the last one
int		next_redir(t_command *cmd, t_lst_redirects *redi, int type)
{
	t_lst_redirects *other;

	other = redi->next;
	while (other)
	{
		if (type == 1)
		{
			if (other->token == STDINN_FILE && other->token == HERE_DOC)
				return (1);
		}
		else
		{
			if (other->token == STDOUT_FILE && other->token == APPEND_FILE)
				return (1);
		}
		other = other->next;
	}
	return (0);
}

void	read_redirect(t_command *commands, t_infos *infos)
{
	int				read_fd;
	t_lst_redirects	*redirect;

	redirect = commands->lst_redirects;
	while (redirect->token != STDINN_FILE && redirect->token != HERE_DOC)
		redirect = redirect->next;
	if (redirect->token == STDINN_FILE)
		read_fd = open(redirect->filename, O_RDONLY);
	else
		read_fd = here_doc(redirect->filename, infos);
	if (read_fd == -1)
		ex_print_error(redirect->filename, strerror(errno), 1);
	if (!next_redir(commands, redirect, 1))
	{
		if (dup2(read_fd, STDIN_FILENO) == -1)
			ex_print_error(redirect->filename, strerror(errno), 1);
	}
	close(read_fd);
}

void	write_redirect(t_command *commands)
{
	int				write_fd;
	t_lst_redirects	*redi;

	redi = commands->lst_redirects;
	while (redi->token != STDOUT_FILE && redi->token != APPEND_FILE)
		redi = redi->next;
	if (redi->token == STDOUT_FILE)
	{
		write_fd = open(redi->filename, O_WRONLY | O_CREAT, 0000644);
		if (write_fd == -1)
			ex_print_error(redi->filename, strerror(errno), 1);
		if (dup2(write_fd, STDOUT_FILENO) == -1)
			ex_print_error(redi->filename, strerror(errno), 1);
	}
	else
	{
		write_fd = open(redi->filename, O_WRONLY | O_APPEND | O_CREAT, 0000644);
		if (write_fd == -1)
			ex_print_error(redi->filename, strerror(errno), 1);
		if (dup2(write_fd, STDOUT_FILENO) == -1)
			ex_print_error(redi->filename, strerror(errno), 1);
	}
}

int	redirect_is_in(t_command *commands)
{
	t_lst_redirects	*redirect;

	if (!commands->lst_redirects)
		return (0);
	redirect = commands->lst_redirects;
	while (redirect)
	{
		if (redirect->token == STDINN_FILE || redirect->token == HERE_DOC)
			return (1);
		redirect = redirect->next;
	}
	return (0);
}

int	redirect_is_out(t_command *commands)
{
	t_lst_redirects	*redirect;

	if (!commands->lst_redirects)
		return (0);
	redirect = commands->lst_redirects;
	while (redirect)
	{
		if (redirect->token == STDOUT_FILE || redirect->token == APPEND_FILE)
			return (1);
		redirect = redirect->next;
	}
	return (0);
}

void	get_read_fd(t_command *commands, t_infos *infos)
{
	if (redirect_is_in(commands))
		return (read_redirect(commands, infos));
	if (commands->order > 1)
	{
		if (dup2(infos->read_fd, STDIN_FILENO) == -1)
			ret_error("Error dup2", 2, 1);
		return ;
	}
}

void	get_write_fd(t_command *commands, t_infos *infos)
{
	if (redirect_is_out(commands))
		return (write_redirect(commands));
	if (commands->next != NULL)
	{
		if (dup2(infos->pipes[1], STDOUT_FILENO) == -1)
			ret_error("Error dup2", 2, 1);
		return ;
	}
	if (commands->next == NULL)
	{
		if (dup2(STDOUT_FILENO, infos->pipes[1]) == -1)
			ret_error("Error dup2", 2, 1);
		return ;
	}
}

void	dup_in_out(t_command *commands, t_infos *infos)
{
	get_read_fd(commands, infos);
	get_write_fd(commands, infos);
}








void	write_no_redi(t_command *cmd, t_infos *infos)
{
	if (cmd->next != NULL)
	{
		if (dup2(infos->pipes[1], STDOUT_FILENO) == -1)
			ret_error("Error dup2", 2, 1);
		return ;
	}
	if (cmd->next == NULL)
	{
		if (dup2(STDOUT_FILENO, infos->pipes[1]) == -1)
			ret_error("Error dup2", 2, 1);
		return ;
	}
}

void	read_no_redi(t_command *cmd, t_infos *infos)
{
	if (cmd->order > 1)
	{
		if (dup2(infos->read_fd, STDIN_FILENO) == -1)
			ret_error("Error dup2", 2, 1);
		return ;
	}
}

int	exec_in(t_command *cmd, t_infos *infos, t_lst_redirects *redi)
{
	int	read_fd;

	if (redi->token == STDINN_FILE)
		read_fd = open(redi->filename, O_RDONLY);
	else
		read_fd = here_doc(redi->filename, infos);
	if (read_fd == -1)
	{
		print_error(redi->filename, strerror(errno));
		return (-1);
	}
	if (!next_redir(cmd, redi, 1))
	{
		if (dup2(read_fd, STDIN_FILENO) == -1)
		{
			print_error(redi->filename, strerror(errno));
			return (-1);
		}
	}
	close(read_fd);
	return (1);
}

int	exec_out(t_command *cmd, t_infos *infos, t_lst_redirects *redi)
{
	int	write_fd;

	if (redi->token == STDOUT_FILE)
		infos->write_fd = open(redi->filename, O_WRONLY | O_CREAT, 0000644);
	else
		infos->write_fd = open(redi->filename, O_WRONLY | O_APPEND | O_CREAT, 0000644);
	if (infos->write_fd == -1)
	{
		print_error(redi->filename, strerror(errno));
		return (-1);
	}
	if (!next_redir(cmd, redi, 0))
	{
		if (dup2(infos->write_fd, STDOUT_FILENO) == -1)
		{
			print_error(redi->filename, strerror(errno));
			return (-1);
		}
	}
	return (1);
}

int	dup_all(t_command *cmd, t_infos *infos, int orexit)
{
	t_lst_redirects *redi;
	int in;
	int out;

	in = 0;
	out = 0;
	redi = cmd->lst_redirects;
	while (redi)
	{
		if (redi->token == STDINN_FILE || redi->token == HERE_DOC)
			in = exec_in(cmd, infos, redi);
		else
			out = exec_out(cmd, infos, redi);
		redi = redi->next;
	}
	if (!in)
		read_no_redi(cmd, infos);
	if (!out)
		write_no_redi(cmd, infos);
	if (orexit && (in < 0 || out < 0))
		exit(1);
	if (!orexit && (in < 0 || out < 0))
		return (-1);
	return (0);
}
