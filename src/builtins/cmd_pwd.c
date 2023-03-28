#include "minishell.h"

void	cmd_pwd(t_infos *infos)
{
	printf("%s\n", infos->pwd);
}