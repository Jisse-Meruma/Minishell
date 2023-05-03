#include "minishell.h"

void	cmd_pwd(t_infos *infos)
{
	ft_putstr_fd(infos->pwd, 1);
	write(1, "\n", 1);
	g_glo.error = 0;
}
