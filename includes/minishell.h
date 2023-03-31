
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
void	cmd_cd(t_infos *infos, char *input);
void	cmd_pwd(t_infos *infos);
void	cmd_env(t_infos *infos);
void	cmd_get_env(t_infos *infos, char *env);
void	cmd_get_env_pwd(t_infos *infos, char *env);
void	cmd_unset(t_infos *infos, char *node);
void	cmd_export(t_infos *infos, char *str);
void	cmd_echo(t_infos *infos, char **str);
int	    cmd_exit(t_infos *infos, char **args);
void    ft_free_lst(t_node* head);

void    mainsignal(t_infos *infos);
void    signal_cmd(t_infos *infos);
int     list_env(char **env, t_infos *infos);
int     ret_error(char *str, int fd, int ret);

//----------------------------------//
//			parser/parser			//
//----------------------------------//
/**
 * @brief This function transforms the input into a parsed linked_list.
 * 
 * @param line line to check.
 * @return Linked_list. if Return == NULL execute an ERROR
 */
char	**parser(char *line);

//----------------------------------//
//			parser/quotes_split		//
//----------------------------------//
/**
 * @brief This function splits as strings the input into a splitted 2d_array.
 * 
 * @param line line to split.
 * @return 2d_array. if Return == NULL execute an ERROR
 */
char	**ft_command_split(char *line);

//----------------------------------//
//			parser/quotes_split		//
//----------------------------------//
/**
 * @brief This function removes the quotes from a 2d_array. Unclosed quotes will just be printed as characters.
 * no need to free the input after use it is done in the fucntion.
 * @param argv 2d_array to remove quotes from.
 * @return new_2d_array with removed quotes . if Return == NULL execute an ERROR
 */
char	**remove_quotes(char *argv[]);

#endif