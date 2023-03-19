/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:58:15 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/19 17:30:33 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *line;
	char *path;

	line = readline("Minishell$ ");
	while (line)
	{
		add_history(line);
		free(line);
		line = readline("Minishell$ ");
	}
	return (0);
}