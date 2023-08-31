/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ret_error.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:05:54 by mbernede      #+#    #+#                 */
/*   Updated: 2023/08/31 13:05:55 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ret_error(char *str, int fd, int ret)
{
	ft_putstr_fd(str, fd);
	return (ret);
}

void	void_ret_error(char *str, int fd)
{
	g_glo.error = 1;
	ft_putstr_fd(str, fd);
}

void	exit_error(char *str, int fd)
{
	g_glo.error = 1;
	ft_putstr_fd(str, fd);
	exit(1);
}
