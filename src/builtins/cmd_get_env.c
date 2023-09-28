/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_get_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:45:07 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/29 01:09:50 by maxb          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//find the env with the same name and update the datas
void	change_env_data(t_infos *infos, char *env, char *data)
{
	t_node	*current;

	current = infos->head;
	while (current != NULL)
	{
		if (!ft_strncmp(env, current->name, ft_strlen(env)))
		{
			if (data)
			{
				if (current->data)
					free(current->data);
				current->data = ft_strdup(data);
			}
			return ;
		}
		current = current->next;
	}
}

//return 1 if env already exist else 0
int	cmd_check_env_exist(t_infos *infos, char *env)
{
	t_node	*current;

	current = infos->head;
	while (current != NULL)
	{
		if (!ft_strncmp(env, current->name, (ft_strlen(env) + 1)))
			return (1);
		current = current->next;
	}
	return (0);
}

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
				void_ret_error("Malloc fail", 2, infos);
			return ;
		}
		current = current->next;
	}
	infos->pwd = getcwd(NULL, 0);
}
