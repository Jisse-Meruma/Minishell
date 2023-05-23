#include "minishell.h"

int init(t_infos *infos, char **envp)
{
	infos->head = NULL;
	if (list_env(envp, infos))
			ret_error("Error in list_env", 1, 1);
	cmd_get_env_pwd(infos, "PWD");
	infos->error = 0;
	g_glo.error = 0;
	return (0);
}
