#include "minishell.h"
#define CHILD 0

void execute_img(t_infos *infos) 
{
    char *path;

    infos->pid = fork();
    if (infos->pid == -1) 
	{
        printf("fork Error\n");
        return ;
    }
    if (infos->pid == CHILD) 
	{
        path = ft_strdup("./imgcat");
        if (path) 
		{
            char *args[] = {"imgcat", "download.png", NULL};
            execve(path, args, NULL);
            printf("execve error\n");
        }
        else 
            printf("ft_strdup error\n");
        return ;
    }
    waitpid(infos->pid, NULL, 0);
}

// void	f() {
// 	system("leaks -q minishell");
// }

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	t_infos		infos;
	t_command	*command;

	if (init(&infos, envp))
		ret_error("Error init\n", 1, 1);
	execute_img(&infos);
	//mainsignal(&infos);
	line = readline("\x1b[1m\x1b[38;2;0;255;255mCeleste-shell$ \x1b[0m");
	while (line)
	{
		add_history(line);
		command = parser(line, &infos);
		if (command && command->cmd_argv)
			start_exec(command, &infos);
		free(line);
		line = readline("\x1b[1m\x1b[38;2;0;255;255mCeleste-shell$ \x1b[0m");
	}
	if (!line)
		printf("exit\n");
	return (0);
}