#include "minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	char	*line;
	t_infos	infos;

	if (init(&infos, envp))
		ret_error("Error init\n", 1, 1);
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
		if (ft_2d_arrlen(argv))
			ifcmd(argv, envp, &infos);
		ft_2dfree(argv);		
		free(line);
		line = readline("Minishell$ ");
	}
	return (0);
}