/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_pwd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:45:05 by mbernede      #+#    #+#                 */
/*   Updated: 2023/08/31 13:45:06 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_pwd(t_infos *infos)
{
	g_glo.error = 0;
	ft_putstr_fd(infos->pwd, 1);
	write(1, "\n", 1);
}
