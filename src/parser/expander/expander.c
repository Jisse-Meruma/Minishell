/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:32:55 by jmeruma           #+#    #+#             */
/*   Updated: 2023/04/24 16:57:38 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	skip_single_quote(char *line, int index)
{
	while (line[index] != '\'' && line[index])
		index++;
	return (index);
}

void	search_env_var(char *line, t_infos *info)
{
	int index;
	int position;
	bool quotes;

	index = 0;
	position = 0;
	quotes = false;
	while (line[index])
	{
		if (line[index] == '\'')
			index = skip_single_quote(line, index);
		if (line[index] == '$')
		{
			ft_substr(line, position, index);
			cmd_get_env_char(info, ) // need to figure out how to do this!
		}
		
		
		
	}
}

bool	find_env_var(char *line)
{
	bool check;
	int index; 

	index = 0;
	check = true;
	while (line[index])
	{
		if (line[index] == '\'')
		{
			index++;
			while (line[index] != '\'')
				index++;
		}
		if (line[index] == '$')
			check = false;
		index++;
	}
	return (check);
}

void	expanding(t_command **lexer, t_infos *info)
{
	t_lexer	*node;

	node = *lexer;
	while (node != NULL)
	{
		if (node->token != TEXT_TOKEN || find_env_var(node->argument))
		{
			node->next;
			continue;
		}
		
		
	}
}