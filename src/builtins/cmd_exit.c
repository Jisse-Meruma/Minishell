#include "minishell.h"

void	cmd_exit(t_infos *infos, char **args)
{
	if (ft_2d_arrlen(args) == 1)
	{
		free(infos->pwd);
		ft_free_lst(infos->head);
		g_glo.error = 0;
		exit(0);
	}
	else if (ft_2d_arrlen(args) == 2)
	{
		if (!ft_isnumber(args[1]))
			ft_putstr_fd("minishell: exit: numeric argument required\n", 1);
		free(infos->pwd);
		ft_free_lst(infos->head);
		exit(ft_atoi(args[1]));
		g_glo.error = 0;
	}
	else
	{
		g_glo.error = 1;
		perror("Error");
	}
}
