#include "minishell.h"
// #include <stdio.h>
// #include <stdbool.h>
// #include <unistd.h>

int	is_endline(char *str, bool *n)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	if (str && str[i] == '-')
		++i;
	while (str && str[i] == 'n')
		++i;
	if (!str[i])
	{
		*n = true;
		return (1);
	}
	return (0);
}

int	skip_endlines(t_command *cmd, bool *n)
{
	int	n_nb;

	n_nb = 0;
	while (cmd->cmd_argv[n_nb + 1])
	{
		if (is_endline(cmd->cmd_argv[n_nb + 1], n))
			n_nb += 1;
		else
			return (n_nb);
	}
	return (n_nb);
}

void	echoprint(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		++i;
	}
}

// echo is working now with str as argv skipping the first argument
void	cmd_echo(t_command *cmd)
{
	bool	n;
	int		i;

	n = false;
	i = 1;
	if (!cmd->cmd_argv[i])
	{
		write(1, "\n", 1);
		return ;
	}
	i += skip_endlines(cmd, &n);
	while (cmd->cmd_argv[i] != NULL)
	{
		echoprint(cmd->cmd_argv[i]);
		++i;
		if (cmd->cmd_argv[i])
			write(1, " ", 1);
	}
	if (n == false)
		write(1, "\n", 1);
	g_glo.error = 0;
	return ;
}
