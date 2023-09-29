/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:45:11 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/29 11:28:12 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_exit(t_infos *infos, int ex, char *arg)
{
	ft_putstr_fd("Celeste-Shell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free(infos->pwd);
	ft_free_lst(infos->head);
	exit(ex);
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

void	exit_no_arg(t_infos *infos, char **args)
{
	if (ft_2d_arrlen(args) == 1)
	{
		free(infos->pwd);
		ft_free_lst(infos->head);
		infos->error = 0;
		exit(0);
	}
}

void	cmd_exit(t_infos *infos, char **args)
{
	exit_no_arg(infos, args);
	exception_exit(infos, args[1]);
	if (!ft_isnumber64(args[1]))
	{
		ft_putstr_fd("exit\n", 1);
		return (call_exit(infos, 2, args[1]));
	}
	if (ft_2d_arrlen(args) > 2)
	{
		ft_putstr_fd("exit\n", 1);
		infos->error = 1;
		ft_putstr_fd("Celeste-Shell: exit: too many arguments\n", 2);
		return ;
	}
	free(infos->pwd);
	ft_free_lst(infos->head);
	exit(ft_atoi(args[1]));
}
