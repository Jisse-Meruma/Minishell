#include <minishell.h>
#include <fcntl.h>

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
	{
		printf("minishell: %s : %s\n", redirect->filename, strerror(errno));
		exit(1);
	}
	if (dup2(read_fd, STDIN_FILENO) == -1)
	{
		printf("minishell: %s : %s\n", redirect->filename, strerror(errno));
		exit(1);
	}
	close(read_fd);
}

void	write_redirect(t_command *commands, t_infos *infos)
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
	{
		printf("minishell: %s : %s\n", redi->filename, strerror(errno));
		exit(1);
	}
		if (dup2(write_fd, STDOUT_FILENO) == -1)
	{
		printf("minishell: %s : %s\n", redi->filename, strerror(errno));
		exit(1);
	}
	}
	else
	{
		write_fd = open(redi->filename, O_WRONLY | O_APPEND | O_CREAT, 0000644);
		if (write_fd == -1)
	{
		printf("minishell: %s : %s\n", redi->filename, strerror(errno));
		exit(1);
	}
		if (dup2(write_fd, STDOUT_FILENO) == -1)
	{
		printf("minishell: %s : %s\n", redi->filename, strerror(errno));
		exit(1);
	}
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
	int	write_fd;

	if (redirect_is_out(commands))
		return (write_redirect(commands, infos));
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

