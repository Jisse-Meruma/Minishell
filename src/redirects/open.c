#include "minishell.h"
#include <fcntl.h>

int	open_here_doc(char *end_of_file, char **path)
{
	int		fd;
	char	*hex;

	printf("[%s]\n", ft_basetoa("0123456789abcdef", 16, (unsigned long)end_of_file));
	hex = ft_basetoa("0123456789abcdef", 16, (unsigned long)end_of_file);
	*path = ft_strjoin("/tmp/here_doc", hex);
	free(hex);
	fd = open(*path, O_RDONLY | O_CREAT | O_WRONLY, 00644);
	return (fd);
}