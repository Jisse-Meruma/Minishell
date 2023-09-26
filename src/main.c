/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 13:53:10 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/26 16:51:53 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <sys/time.h>
// #include <sys/wait.h>


//heredoc signal
//pipe
//cat cat ls


int	g_signal;

int	exit_properly(t_infos *infos, char *line)
{
	if (!line)
		ft_printf("exit\n");
	free_infos(infos);
	return (0);
}

int	no_start(int argc, t_infos *infos, char **envp)
{
	if (argc != 1)
		return (ret_error("Too many Arguments!\n", 2, 1));
	if (init(infos, envp))
		return (EXIT_FAILURE);
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_infos		infos;
	t_command	*command;

	(void)argv;
	if (no_start(argc, &infos, envp))
		return (EXIT_FAILURE);
	line = readline("Celeste-shell$ ");
	while (line)
	{
		if (g_signal)
		{
			infos.error = g_signal;
			g_signal = 0;
		}
		add_history(line);
		command = parser(line, &infos);
		if (command && command->cmd_argv)
			start_exec(command, &infos);
		free_cmd_struct(command);
		free(line);
		line = readline("Celeste-shell$ ");
	}
	return (exit_properly(&infos, line));
}
