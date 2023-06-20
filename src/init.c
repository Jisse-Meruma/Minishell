#include "minishell.h"

//cmd_export(infos, "SHLVL=1");

void	add_one_shlvl(t_infos *infos, int shlvlnb)
{
	char *strshlvl;
	char *export_str;

	++shlvlnb;
	strshlvl = ft_itoa(shlvlnb);
	if (!strshlvl)
		return (void_ret_error("Error in SHLVL\n", 2));
	export_str = ft_strjoin("SHLVL=", strshlvl);
	if (!export_str)
		return (void_ret_error("Error in SHLVL\n", 2));
	exec_export(infos, export_str);
	free(export_str);
	free(strshlvl);
}

void	updateshlvl(t_infos *infos)
{
	char *shlvl;
	int shlvlnb;

	shlvl = cmd_get_env_char(infos, "SHLVL");
	if (!shlvl)
		return (void_ret_error("Error in SHLVL\n", 2));
	if (!ft_isnumber(shlvl))
	{
		exec_export(infos, "SHLVL=1");
		return ;
	}
	shlvlnb = ft_atoi(shlvl);
	if (shlvlnb <= -1)
		exec_export(infos, "SHLVL=0");
	else if (shlvlnb == 999)
		exec_export(infos, "SHLVL=");
	else if (shlvlnb >= 1000)
	{
		++shlvlnb;
		ft_putstr_fd("bash: warning: shell level (", 2);
		ft_putstr_fd(ft_itoa(shlvlnb), 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		exec_export(infos, "SHLVL=1");
	}
	else
		add_one_shlvl(infos, shlvlnb);
}

void	add_shlvl(t_infos *infos)
{
	if (cmd_check_env_exist(infos, "SHLVL"))
		updateshlvl(infos);
	else
		exec_export(infos, "SHLVL=1");
}

int	init(t_infos *infos, char **envp)
{
	infos->head = NULL;
	if (list_env(envp, infos))
		ret_error("Error in list_env", 2, 1);
	cmd_get_env_pwd(infos, "PWD");
	add_shlvl(infos);
	g_glo.error = 0;
	return (0);
}
