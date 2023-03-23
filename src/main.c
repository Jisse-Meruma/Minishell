/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:58:15 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/23 12:16:30 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char *line;

	line = readline("Minishell$ ");
	while (line)
	{
		add_history(line);
		argv = ft_split(line, ' ');
		execute_cmd(argv, envp);
		ft_2dfree(argv);		
		free(line);
		line = readline("Minishell$ ");
	}
	return (0);
}