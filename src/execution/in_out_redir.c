#include <minishell.h>
#include <fcntl.h>

void print_fd_contents(int fd) {
    char buffer[1024];
    ssize_t bytesRead;

    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }

    if (bytesRead < 0) {
        perror("Error reading from file descriptor");
        exit(EXIT_FAILURE);
    }
}

void	read_redirect(t_command *commands, t_infos *infos)
{
	int read_fd;

	if (commands->lst_redirects->token == STDINN_FILE)
	{
		read_fd = open(commands->lst_redirects->filename, O_RDONLY);
		if (read_fd == -1)
			ret_error("Error read", 2, 1);
		if (dup2(read_fd, STDIN_FILENO) == -1)
			ret_error("Error dup2", 2, 1);
		return ;
	}
}

void	write_redirect(t_command *commands, t_infos *infos)
{
	int write_fd;

	if (commands->lst_redirects->token == STDOUT_FILE)
	{
		write_fd = open(commands->lst_redirects->filename, O_WRONLY | O_APPEND | O_CREAT, 0000644);
		if (write_fd == -1)
			ret_error("Error read", 2, 1);
		if (dup2(write_fd, STDOUT_FILENO) == -1)
			ret_error("Error dup2", 2, 1);
		return ;
	}
}

void	get_read_fd(t_command *commands, t_infos *infos)
{
	// if (commands->lst_redirects)
	// 	return (read_redirect(commands, infos));
	if (commands->order > 1)
	{
		if (dup2(infos->read_fd, STDIN_FILENO) == -1)
			ret_error("Error dup2", 2, 1);
		return ;
	}
}

void	get_write_fd(t_command *commands, t_infos *infos)
{
	int write_fd;

	// if (commands->lst_redirects)
	// 	return (write_redirect(commands, infos));
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

