#include "minishell.h"

char *env_str(t_node *current)
{
	char *str;

	str = ft_strdup(current->name);
	if (!str)
		return (NULL);
	str = ft_strjoin_free(str, "=");
	if (!str)
		return (NULL);
	if (current->data)
		str = ft_strjoin_free(str, current->data);
	return (str);
}

//warning : ret_error returns an int
char	**get_envp(t_infos *infos)
{
	t_node	*current;
	char	**envp;
	int		i;
	char	*temp;

	current = infos->head;
	i = 0;
	envp = (char **) malloc((ft_our_lst_size(current) + 1) * sizeof(char *));
	if (!envp)
		return (ret_error("Malloc error", 2, 0), NULL);
	while (current)
	{
		temp = env_str(current);
		envp[i] = temp;
		current = current->next;
		++i;
	}
	envp[i] = NULL;
	return (envp);
}
