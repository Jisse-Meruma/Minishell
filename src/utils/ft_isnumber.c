/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isnumber.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:11:00 by mbernede      #+#    #+#                 */
/*   Updated: 2023/08/31 13:11:19 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnumber(char *str)
{
	int	i;
	int	numb;

	i = 0;
	if (!str)
		return (0);
	if (ft_atoi_overflow(str, &numb))
		return (0);
	if (str[0] && (str[0] == '-' || str[0] == '+'))
	{
		++i;
		if (!str[i])
			return (0);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}
