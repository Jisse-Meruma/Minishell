
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

void	ifcmd(char *argv[], char *envp[]);
int     compare(char *s1, char *s2);
void	cmd_pwd();
void	cmd_env();

char	**ft_command_split(char *line);
void	ifcmd(char *argv[], char *envp[]);
int     compare(char *s1, char *s2);
void	cmd_pwd();
void	cmd_env();

char	**ft_command_split(char *line);

#endif