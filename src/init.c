#include "minishell.h"

int	init(t_infos *infos, char **envp)
{
	infos->head = NULL;
	infos->write_fd = 0;
	if (list_env(envp, infos))
		ret_error("Error in list_env", 2, 1);
	cmd_get_env_pwd(infos, "PWD");
	add_shlvl(infos);
	g_glo.error = 0;
	return (0);
}
