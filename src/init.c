#include "minishell.h"

//cmd_export(infos, "SHLVL=1");

void	add_shlvl(t_infos *infos)
{
	return ;
}

int init(t_infos *infos, char **envp)
{
	infos->head = NULL;
	if (list_env(envp, infos))
			ret_error("Error in list_env", 1, 1);
	add_shlvl(infos);
	cmd_get_env_pwd(infos, "PWD");
	infos->error = 0;
	g_glo.error = 0;
	return (0);
}
