#include "minishell.h"

int	cmd_exit(t_infos *infos, char **args)
{
    if (ft_2d_arrlen(args) != 1)
    {
        infos->error = 1;
        printf("exit: too many arguments\n");
        return (infos->error);
    }
    free(infos->pwd);
    ft_free_lst(infos->head);
    return (infos->error);
}