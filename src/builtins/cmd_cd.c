#include "minishell.h"
#include <string.h>

void	update_old_and_pwd(t_infos *infos)
{
	char	s[1024];

	if (cmd_check_env_exist(infos, "OLDPWD"))
		change_env_data(infos, "OLDPWD", infos->pwd);
	free(infos->pwd);
	infos->pwd = ft_strdup(getcwd(s, sizeof(s)));
	if (cmd_check_env_exist(infos, "PWD"))
		change_env_data(infos, "PWD", infos->pwd);
}

void	cmd_cd(t_infos *infos, char *input)
{
	char	*str;

	if (!input)
	{
		if (!cmd_check_env_exist(infos, "HOME"))
			return (void_ret_error("bash: cd: HOME not set\n", 2));
		str = ft_strdup("/");
	}
	else
		str = ft_strdup(input);
	if (!str)
		void_ret_error("Malloc Error", 2);
	if (chdir(str))
	{
		printf("bash: cd: %s : %s\n", str, strerror(errno));
		g_glo.error = 1;
		return ;
	}
	update_old_and_pwd(infos);
}
