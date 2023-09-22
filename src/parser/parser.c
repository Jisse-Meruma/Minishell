/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmeruma <jmeruma@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 11:55:22 by jmeruma       #+#    #+#                 */
/*   Updated: 2023/09/22 13:52:59 by mbernede      ########   odam.nl         */
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
		return (void_ret_error("Parsing ERROR\n", 2, infos), NULL);
	tokenizer(&lexer);
	if (expanding(&lexer, infos))
		return (lexer_free(&lexer), infos->error = 1, NULL);
	if (remove_quotes(&lexer))
		return (lexer_free(&lexer), \
		void_ret_error("Quotes Fial\n", 2, infos), NULL);
	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (lexer_free(&lexer), infos->error = 1, NULL);
	if (parse_struct_command(&lexer, command))
		return (lexer_free(&lexer), infos->error = 2, NULL);
	lexer_free(&lexer);
	return (command);
}
