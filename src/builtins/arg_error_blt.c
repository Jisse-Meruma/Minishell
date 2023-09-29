/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   arg_error_blt.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mbernede <mbernede@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:45:20 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/29 11:21:29 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	not_valid_id(char *str, char *cmd, t_infos *infos)
{
	infos->error = 1;
	ft_putstr_fd("Celeste-shell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

void	print_error(char *str, char *error, t_infos *infos)
{
	ft_putstr_fd("Celeste-shell: ", 2);
	if (str && compare(str, "$"))
		ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	infos->error = 1;
}

void	ex_print_error(char *str, char *error, int exitnb)
{
	ft_putstr_fd("Celeste-shell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
	exit(exitnb);
}
