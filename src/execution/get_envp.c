#include "minishell.h"
#include <string.h>

char *get_envp(t_infos *infos)
{
	t_node	*current;
	char	**envp;
	int		i;
	char	*temp;

	current = infos->head;
	i = 0;
	envp = (char **) malloc((ft_our_lst_size(current) + 1));
	while (current)
	{
		temp = ft_strjoin(current->name, "=");
		if (current->data)
			temp = ft_strjoin_free(temp, current->data);
		envp[i] = temp;
		free(temp);
		current = current->next;
		++i;
	}
	ft_2d_print(envp);
}
