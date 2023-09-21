/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:45:11 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/21 16:33:03 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_exit(t_infos *infos)
{
	ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
	free(infos->pwd);
	ft_free_lst(infos->head);
	exit(2);
}

void	exception_exit(t_infos *infos, char *str)
{
	int	ex_nb;

	ex_nb = -1;
	if (!compare(str, "-9223372036854775807"))
		ex_nb = 1;
	else if (!compare(str, "-9223372036854775808"))
		ex_nb = 0;
	if (ex_nb != -1)
	{
		free(infos->pwd);
		ft_free_lst(infos->head);
		exit(ex_nb);
	}
}

void	cmd_exit(t_infos *infos, char **args)
{
	if (ft_2d_arrlen(args) == 1)
	{
		free(infos->pwd);
		ft_free_lst(infos->head);
		infos->error = 0;
		exit(0);
	}
	else if (ft_2d_arrlen(args) == 2)
	{
		exception_exit(infos, args[1]);
		if (!ft_isnumber64(args[1]))
			return (call_exit(infos));
		free(infos->pwd);
		ft_free_lst(infos->head);
		exit(ft_atoi(args[1]));
	}
	else
	{
		infos->error = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
}
