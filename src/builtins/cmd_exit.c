#include "minishell.h"

void	cmd_exit(t_infos *infos)
{
    free(infos->pwd);
    ft_free_lst(infos->head);
    exit(infos->error);
}