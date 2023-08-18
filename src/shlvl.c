#include "minishell.h"

void	print_sh_err(int shlvlnb)
{
	ft_putstr_fd("bash: warning: shell level (", 2);
	ft_putstr_fd(ft_itoa(shlvlnb), 2);
	ft_putstr_fd(") too high, resetting to 1\n", 2);
}

bool	add_one_shlvl(t_infos *infos, int shlvlnb)
{
	char *strshlvl;
	char *export_str;

	++shlvlnb;
	strshlvl = ft_itoa(shlvlnb);
	if (!strshlvl)
		return (void_ret_error("Error in SHLVL\n", 2), false);
	export_str = ft_strjoin("SHLVL=", strshlvl);
	if (!export_str)
	{
		free(strshlvl);
		return (void_ret_error("Error in SHLVL\n", 2), false);
	}
	exec_export(infos, export_str);
	free(export_str);
	free(strshlvl);
	return (true);
}

bool	updateshlvl(t_infos *infos)
{
	char *shlvl;
	int shlvlnb;

	shlvl = cmd_get_env_char(infos, "SHLVL");
	if (!shlvl)
		return (void_ret_error("Error in SHLVL\n", 2), false);
	if (!ft_isnumber(shlvl))
		return (exec_export(infos, "SHLVL=1"), false);
	shlvlnb = ft_atoi(shlvl);
	if (shlvlnb <= -1)
		exec_export(infos, "SHLVL=0");
	else if (shlvlnb == 999)
		exec_export(infos, "SHLVL=");
	else if (shlvlnb >= 1000)
	{
		++shlvlnb;
		print_sh_err(shlvlnb);
		exec_export(infos, "SHLVL=1");
	}
	else
	{
		if (!add_one_shlvl(infos, shlvlnb))
			return (false);
	}
	return (true);
}

bool	add_shlvl(t_infos *infos)
{
	if (cmd_check_env_exist(infos, "SHLVL"))
	{
		if (!updateshlvl(infos))
			return (false);
	}
	else
		exec_export(infos, "SHLVL=1");
	
	return (true);
}
