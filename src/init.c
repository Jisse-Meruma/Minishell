#include "minishell.h"

/**
 * @brief init will fill the linkedlist of env variables and also get the current pwd directory to keep it in case we move
 * 
 * @param infos 
 * @param envp 
 * @return int 
 */
int init(t_infos *infos, char **envp)
{
    if (list_env(envp, infos))
		  ret_error("Error in list_env", 1, 1);
    cmd_get_env_pwd(infos, "PWD");
    return (0);
}