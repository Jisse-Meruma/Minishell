#include "minishell.h"

void	free_redirect_lst(t_lst_redirects *redirect)
{
	t_lst_redirects	*nfree;

	while (redirect)
	{
		nfree = redirect;
		free(nfree->filename);
		redirect = redirect->next;
		free(nfree);
	}
}

void	free_cmd_struct(t_command *commands)
{
	t_command	*nfree;

	while (commands)
	{
		nfree = commands;
		ft_2dfree(commands->cmd_argv);
		free_redirect_lst(commands->lst_redirects);
		commands = commands->next;
		free(nfree);
	}
}
