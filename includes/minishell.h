/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeruma <jmeruma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 15:59:25 by jmeruma           #+#    #+#             */
/*   Updated: 2023/03/23 12:56:26 by jmeruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>


//----------------------------------//
//			Path_creation			//
//----------------------------------//
/**
 * @brief This function checks if the command given is a command that exist.
 * 
 * @param command command to check.
 * @return path of the given command. if path does not exist return NULL
 */
char	*path_creation(char *command);

void	execute_cmd(char *argv[], char *envp[]);

char	**ft_command_split(char *line);

#endif