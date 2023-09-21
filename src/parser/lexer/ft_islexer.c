/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 11:55:49 by jmeruma           #+#    #+#             */
/*   Updated: 2023/09/21 11:55:50 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isquote(char quote)
{
	if (quote == '\'' || quote == '\"')
		return (true);
	return (false);
}

int	ft_ismeta(char meta)
{
	if (meta == '>' || meta == '<' || meta == '|')
		return (true);
	return (false);
}

int	ft_isspecial(char c)
{
	if (ft_isquote(c) || ft_ismeta(c))
		return (true);
	return (false);
}

int	double_meta(int index, char *line)
{
	if (line[index] == '|' && line[index + 1] == '|')
		return (0);
	else if (line[index] == '>' && line[index + 1] == '>')
		return (2);
	else if (line[index] == '<' && line[index + 1] == '<')
		return (2);
	return (1);
}
