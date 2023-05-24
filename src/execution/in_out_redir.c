#include <minishell.h>
# include <fcntl.h>

void	get_read_fd(t_command *commands, t_infos *infos)
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
	if (commands->order >= 2)
	{
		if (dup2(commands->read_fd, STDIN_FILENO) == -1)
			ret_error("Error dup2", 2, 1);
		return ;
	}
}

// void	get_write_fd(t_command *commands, t_infos *infos)
// {
// 	int write_fd;
// 	if (commands->lst_redirects->token == STDOUT_FILE)
// 	{
// 		write_fd = open(commands->lst_redirects->filename, O_WRONLY | O_TRUNC | O_CREAT);
// 		if (write_fd == -1)
// 			ret_error("Error opening the write file", 2, 1);
// 		if (dup2(write_fd, STDOUT_FILENO) == -1)
// 			ret_error("Error dup2", 2, 1);
// 		return ;
// 	}
// 	if 
// 	if (commands->order >= 2)
// 	{
// 		if (dup2(commands->read_fd, STDIN_FILENO) == -1)
// 			ret_error("Error dup2", 2, 1);
// 		return ;
// 	}
// }

void	dup_in_out(t_command *commands, t_infos *infos)
{
	if (commands->lst_redirects->token == STDINN_FILE)
		get_read_fd(commands, infos);
}