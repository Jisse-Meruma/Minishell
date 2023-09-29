/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_cd.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:45:17 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/29 11:49:00 by mbernede      ########   odam.nl         */
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
		ft_putstr_fd(ER_CD_CURDIR, 2);
		ft_putstr_fd(" getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		infos->error = 1;
	}
	infos->pwd = ft_strdup(s);
	if (cmd_check_env_exist(infos, "PWD"))
		change_env_data(infos, "PWD", infos->pwd);
}

void	cmd_cd(t_infos *infos, char **input)
{
	char	*str;

	if (ft_2d_arrlen(input) > 2)
		return (void_ret_error(" too many arguments", 2, infos));
	if (!input[1])
	{
		if (!cmd_check_env_exist(infos, "HOME"))
			return (void_ret_error(ER_CD_HOME, 2, infos));
		str = ft_strdup(cmd_get_env_char(infos, "HOME"));
	}
	else
		str = ft_strdup(input[1]);
	if (!str)
		void_ret_error("Malloc Error", 2, infos);
	if (chdir(str) < 0)
	{
		write(2, "Celeste-shell: cd: ", 15);
		perror(str);
		infos->error = 1;
		free(str);
		return ;
	}
	free(str);
	update_old_and_pwd(infos);
	infos->error = 0;
}
