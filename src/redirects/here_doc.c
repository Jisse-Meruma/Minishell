#include "minishell.h"
#include "h_color.h"

#define INVALID -1

int	here_doc(char *end_of_file, t_infos *infos)
{
	int		fd;
	char	*path;
	char	*line;

	fd = open_here_doc(end_of_file, &path);
	if (fd == INVALID)
		return (INVALID);
	line = readline("\x1b[1m\x1b[38;2;128;0;128mBadeline> \x1b[0m");
	while (line)
	{
		if (!ft_strncmp(line, end_of_file, ft_strlen(end_of_file) + 1))
		{
			free(line);
			break ;
		}
		if (!find_env_var(line))
			line = search_env_var(line, infos);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("\x1b[1m\x1b[38;2;128;0;128mBadeline> \x1b[0m");
	}
	return (here_doc_unlink_and_close(path, fd));
}
