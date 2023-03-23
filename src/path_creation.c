#include "minishell.h"
#define FOUND 0

static char *path_command_join(char **bin_dir, char *command, int index)
{
	char *path_command;

	path_command = ft_strjoin(bin_dir[index], "/");
	if (!path_command)
	{
		free(bin_dir);
		return (NULL);
	}
	path_command = ft_strjoin_free(path_command, command);
	if (!path_command)
	{
		free(bin_dir);
		return (NULL);
	}
	return (path_command);
}

static char	*path_finder(char *path_var, char *command)
{
	int		index;
	char	**bin_dir;
	char	*path_command;

	index = 0;
	bin_dir = ft_split(path_var, ':');
	if (!bin_dir)
		printf("malloc ERROR\n");
	while (bin_dir[index] != NULL)
	{
		path_command = path_command_join(bin_dir, command, index);
		if (access(path_command, F_OK | X_OK) == FOUND)
		{
			ft_2dfree(bin_dir);
			return (path_command);
		}
		free(path_command);
		index++;
	}
	ft_2dfree(bin_dir);
	return (NULL);
}

char	*path_creation(char *command)
{
	char	*path_var;
	char	*path_command;

	if (*command == '\0')
		return (NULL);
	if (access(command, F_OK | X_OK) == FOUND)
		return (command);
	path_var = getenv("PATH");
	if (!path_var)
		printf("command not found\n");
	path_command = path_finder(path_var, command);
	if (!path_command)
		printf("command not found\n");
	return (path_command);
}