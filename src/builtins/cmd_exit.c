/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_exit.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:45:11 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/06 15:34:24 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check the frees of exit
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
		if (!ft_isnumber(args[1]))
			ft_putstr_fd("minishell: exit: numeric argument required\n", 1);
		free(infos->pwd);
		ft_free_lst(infos->head);
		exit(ft_atoi(args[1]));
	}
	else
	{
		infos->error = 1;
		perror("Error");
	}
}
