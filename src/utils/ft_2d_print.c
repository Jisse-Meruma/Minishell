/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_2d_print.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:11:23 by mbernede      #+#    #+#                 */
/*   Updated: 2023/08/31 13:11:24 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_2d_print(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putstr_fd(str[i], 1);
		write(1, "\n", 1);
		++i;
	}
}
