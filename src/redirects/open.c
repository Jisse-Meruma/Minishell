#include "minishell.h"
#include <fcntl.h>

int	open_here_doc(char *end_of_file)
{
	printf("[%s]\n", ft_basetoa("0123456789abcdef", 16, end_of_file));
}