#include "minishell.h"

/**
 * @brief its literally the getenv and search the string env in the linked list from the infos
 * 
 * @param infos
 * @param env 
 */
void	cmd_get_env(t_infos *infos, char *env)
{
    t_node *current;

    current = infos->head;
    while (current != NULL) 
    {
        if (!ft_strncmp(env, current->name, ft_strlen(env)))
        {
            printf("%s\n",current->data);
            return ;
        }
        current = current->next;
    }
}

//used in init to get the pwd at the start of the program and save it in the structure
void	cmd_get_env_pwd(t_infos *infos, char *env)
{
    t_node *current;

    current = infos->head;
    while (current != NULL) 
    {
        if (!ft_strncmp(env, current->name, ft_strlen(env)))
        {
            infos->pwd = ft_strdup(current->data);
            return ;
        }
        current = current->next;
    }
    infos->pwd = getcwd(NULL, 0);
}