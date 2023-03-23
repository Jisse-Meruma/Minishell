/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:58:15 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/23 13:00:49 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	char	*line;

	line = readline("Minishell$ ");
	while (line)
	{
		i = 0;
		add_history(line);
		argv = ft_command_split(line);
		while (argv[i] != NULL)
		{
			printf("[%d]-[%s]\n", i, argv[i]);
			i++;
		}
		execute_cmd(argv, envp);
		ft_2dfree(argv);		
		free(line);
		line = readline("Minishell$ ");
	}
	return (0);
}