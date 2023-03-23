/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   compare.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/03/23 12:58:50 by mbernede      #+#    #+#                 */
/*   Updated: 2023/03/23 13:03:59 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	compare(char *s1, char *s2)
{
	int i;

    i = 0;
    while (s1[i])
    {
        if (ft_toupper(s1[i]) == ft_toupper(s2[i]))
            ++i;
        else
            return (-1);
    }
    if (s1[i] == s2[i])
        return (0);
    else
        return (-1);
}