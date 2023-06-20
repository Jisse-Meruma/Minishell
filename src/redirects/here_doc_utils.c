#include "minishell.h"
#define INVALID -1
#include <fcntl.h>

int	here_doc_unlink_and_close(char *path, int old_fd)
{
	int	new_fd;

	close(old_fd);
	new_fd = open(path, O_RDONLY);
	if (unlink(path) == -1)
		return (INVALID);
	free(path);
	return (new_fd);
}
