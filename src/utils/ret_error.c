#include "minishell.h"

int	ret_error(char *str, int fd, int ret)
{
	ft_putstr_fd(str, fd);
	return (ret);
}

void	void_ret_error(char *str, int fd)
{
	g_glo.error = 1;
	ft_putstr_fd(str, fd);
}

void	exit_error(char *str, int fd)
{
	g_glo.error = 1;
	ft_putstr_fd(str, fd);
	exit(1);
}
