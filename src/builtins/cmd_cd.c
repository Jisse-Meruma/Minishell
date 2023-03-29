#include "minishell.h"
#include <string.h>

// manually adding /USERS/{NAME}/ to the input for the path and join to the rest
// if the call is ~/Desktop/minishell, will do /Users/{intra}/Desktop/minishell
char    *wave(t_infos *infos, char *str)
{
	int i;
	int slash;
	char *sub;
	char *path;

	if (ft_strlen(str) > 2 && str[0] == '~' && str[1] == '/')
	{
		i = 0;
		slash = 0;
		while (infos->pwd[i] && slash <= 2)
		{
			if (infos->pwd[i] == '/')
				slash++;
			++i;
		}
		sub = ft_substr(infos->pwd, 0, i);
		path = ft_substr(str, 2, ft_strlen(str) - 2);
		free(str);
		return (ft_strjoin_free(sub, path));
	}
	return (str);
}

void	cmd_cd(t_infos *infos, char *input)
{
	char s[1024];
	char *str;

	str = ft_strdup(input);
	if (!str)
		return ;
	str = wave(infos, str);
	infos->error = chdir(str);
	if (infos->error)
	{
		printf("cd: %s : %s\n", strerror(errno), str);
		infos->error = 1;
		return ;
	}
	free(infos->pwd);
	infos->pwd = ft_strdup(getcwd(s, sizeof(s)));
}