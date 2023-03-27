
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

void	ifcmd(char *argv[], char *envp[]);
int     compare(char *s1, char *s2);
void	cmd_pwd();
void	cmd_env();

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