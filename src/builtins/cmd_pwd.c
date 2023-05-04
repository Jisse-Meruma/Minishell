#include "minishell.h"

void	cmd_pwd(t_infos *infos)
{
	g_glo.error = 0;
	ft_putstr_fd(infos->pwd, 1);
	write(1, "\n", 1);
}
