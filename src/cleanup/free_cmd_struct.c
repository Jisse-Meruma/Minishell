/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_cmd_struct.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/21 16:33:23 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/21 16:33:24 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
