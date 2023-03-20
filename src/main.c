/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jisse <jisse@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:58:15 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/20 12:08:40 by jisse            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *line;

	line = readline("Minishell$ ");
	while (line)
	{
		add_history(line);
		free(line);
		line = readline("Minishell$ ");
	}
	return (0);
}