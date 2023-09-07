/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_cd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:45:17 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/07 15:13:54 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_old_and_pwd(t_infos *infos)
{
	char	s[1024];

	if (cmd_check_env_exist(infos, "OLDPWD"))
		change_env_data(infos, "OLDPWD", infos->pwd);
	free(infos->pwd);
	if (!getcwd(s, sizeof(s)))
	{
		printf("minishell: cd: error retrieving current directory: getcwd: cannot access parent directories: %s\n", strerror(errno));
		infos->error = 1;
	}
	infos->pwd = ft_strdup(s);
	if (cmd_check_env_exist(infos, "PWD"))
		change_env_data(infos, "PWD", infos->pwd);
}

void	cmd_cd(t_infos *infos, char *input)
{
	char	*str;

	if (!input)
	{
		if (!cmd_check_env_exist(infos, "HOME"))
			return (void_ret_error("minishell: cd: HOME not set\n", 2, infos));
		str = cmd_get_env_char(infos, "HOME");
	}
	else
		str = ft_strdup(input);
	if (!str)
		void_ret_error("Malloc Error", 2, infos);
	if (chdir(str) < 0)
	{
		write(2, "minishell: cd: ", 15);
		perror(str);
		infos->error = 1;
		free(str);
		return ;
	}
	free(str);
	update_old_and_pwd(infos);
}
