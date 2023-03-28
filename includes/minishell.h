
#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include "infos.h"
#include "libft.h"
#include <stdbool.h>
#include <signal.h>
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
int     init(t_infos *infos, char **envp);


void	ifcmd(char *argv[], char *envp[], t_infos *infos);
int     compare(char *s1, char *s2);

void	execute_cmd(char *argv[], char *envp[], t_infos *infos);
void	cmd_cd(t_infos *infos);
void	cmd_pwd(t_infos *infos);
void	cmd_env(t_infos *infos);
void	cmd_get_env(t_infos *infos, char *env);
void	cmd_get_env_pwd(t_infos *infos, char *env);

void    signal_cmd(t_infos *infos);
int     list_env(char **env, t_infos *infos);
int     ret_error(char *str, int fd, int ret);

char	**ft_command_split(char *line);

#endif