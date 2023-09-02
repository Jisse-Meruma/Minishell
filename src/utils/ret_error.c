/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:05:54 by mbernede          #+#    #+#             */
/*   Updated: 2023/09/02 17:04:29 by jmeruma          ###   ########.fr       */
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

void	minishell_perror(char *str)
{
	write(1, "Celeste-shell: ", 15);
	perror(str);
}
