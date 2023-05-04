#include "minishell.h"

//PRINT the data of a certain env var name
void	cmd_get_env(t_infos *infos, char *env)
{
	t_node	*current;

	current = infos->head;
	while (current != NULL)
	{
		if (!ft_strncmp(env, current->name, ft_strlen(env)))
		{
			printf("%s\n", current->data);
			return ;
		}
		current = current->next;
	}
}

//RETURN data of env name
char	*cmd_get_env_char(t_infos *infos, char *env)
{
	t_node	*current;

	current = infos->head;
	if (!env)
		return (NULL);
	while (current != NULL)
	{
		if (!ft_strncmp(env, current->name, ft_strlen(env) + 1))
			return (current->data);
		current = current->next;
	}
	return (NULL);
}

//used in init to get the pwd at the start of the program and save it
void	cmd_get_env_pwd(t_infos *infos, char *env)
{
	t_node	*current;

	current = infos->head;
	while (current != NULL)
	{
		if (!ft_strncmp(env, current->name, ft_strlen(env)))
		{
			infos->pwd = ft_strdup(current->data);
			if (!infos->pwd)
				void_ret_error("Malloc fail", 2);
			return ;
		}
		current = current->next;
	}
	infos->pwd = getcwd(NULL, 0);
}
