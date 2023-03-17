/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:58:15 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/17 17:32:03 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *line;

	line = readline("Minishell$");
	while (line)
	{
		printf("%s", line);
		free(line);
		line = readline("Minishell$");
	}
	return (0);
}