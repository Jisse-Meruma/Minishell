/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split_first.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:50:37 by mbernede      #+#    #+#                 */
/*   Updated: 2023/08/31 15:17:11 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_end(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		++i;
	if (i != ft_strlen(str))
		return (2);
	return (1);
}

char	**no_split(char *str, char **str2d)
{
	str2d[0] = ft_strdup(str);
	if (!str2d[0])
		return (free(str2d), NULL);
	return (str2d);
}

int	split_half(int *i, char c, char *str, char **str2d)
{
	while (str[*i])
	{
		if (str[*i] == c)
		{
			str2d[0] = ft_substr(str, 0, *i);
			if (!str2d[0])
				return (free(str2d), 1);
			(*i)++;
			break ;
		}
		(*i)++;
	}
	return (0);
}

char	**ft_split_first(char *str, char c)
{
	int		i;
	char	**str2d;
	int		end;

	end = get_end(str, c);
	str2d = (char **)ft_calloc(end + 1, sizeof(char *));
	if (!str2d)
		return (NULL);
	if (end == 1)
		return (no_split(str, str2d));
	i = 0;
	if (split_half(&i, c, str, str2d))
		return (NULL);
	if (str[i] && str[i] == c)
		++i;
	if (ft_strlen(str) != i)
	{
		str2d[1] = ft_substr(str, i, (ft_strlen(str) - i));
		if (!str2d[1])
			return (ft_2dfree(str2d), NULL);
	}
	return (str2d);
}
