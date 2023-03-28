#include <unistd.h>
#include "minishell.h"

int	ret_error(char *str, int fd, int ret)
{
	ft_putstr_fd(str, fd);
	return (ret);
}
