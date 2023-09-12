/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/12 13:53:10 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/12 13:53:11 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <sys/time.h>
// #include <sys/wait.h>
t_glo	g_glo;

// void	execute_img(t_infos *infos)
// {
// 	char	*path;

// 	infos->pid = fork();
// 	if (infos->pid == -1)
// 	{
// 		printf("fork Error\n");
// 		return ;
// 	}
// 	if (infos->pid == CHILD)
// 	{
// 		path = ft_strdup("./imgcat");
// 		if (path)
// 		{
// 			char	*args[] = {"imgcat", "download.png", NULL};
// 			execve(path, args, NULL);
// 			printf("execve error\n");
// 		}
// 		else
// 			printf("ft_strdup error\n");
// 		return ;
// 	}
// 	waitpid(infos->pid, NULL, 0);
// }

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_infos		infos;
	t_command	*command;

	(void)argc;
	(void)argv;
	if (init(&infos, envp))
		return (EXIT_FAILURE);
	mainsignal();
	line = readline("Celeste-shell$ ");
	while (line)
	{
		add_history(line);
		command = parser(line, &infos);
		if (!command)
			infos.error = 1;
		if (command && command->cmd_argv)
			start_exec(command, &infos);
		free_cmd_struct(command);
		free(line);
		line = readline("Celeste-shell$ ");
	}
	if (!line)
		ft_printf("exit\n");
	free_infos(&infos);
	return (0);
}
