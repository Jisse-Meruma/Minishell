#include "minishell.h"

void	cmd_cd(t_infos *infos, char *input)
{
    char s[1024];

    if (chdir(input))
    {
        printf("ERROR CHDIR\n");
        return ;
    }
    free(infos->pwd);
    infos->pwd = ft_strdup(getcwd(s, sizeof(s)));
}