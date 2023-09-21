/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmeruma <jmeruma@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 11:55:22 by jmeruma       #+#    #+#                 */
/*   Updated: 2023/09/21 17:26:50 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*parser(char *line, t_infos *infos)
{
	t_lexer		*lexer;
	t_command	*command;

	lexer = NULL;
	if (*line == '\0')
		return (NULL);
	if (ft_lexer(&lexer, line))
		return (NULL);
	tokenizer(&lexer);
	if (expanding(&lexer, infos))
		return (lexer_free(&lexer), NULL);
	remove_quotes(&lexer);
	command = ft_calloc(1, sizeof(t_command));
	if (!command)
	{
		infos->error = 1;
		return (lexer_free(&lexer), NULL);
	}
	if (parse_struct_command(&lexer, command))
	{
		infos->error = 2;
		return (lexer_free(&lexer), NULL);
	}
	lexer_free(&lexer);
	return (command);
}
