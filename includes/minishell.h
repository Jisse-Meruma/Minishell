
#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include "infos.h"
#include "libft.h"
#include "struct.h"
#include <stdbool.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#define ERROR 1
#define SUCCES 0


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
char    *cmd_get_env_char(t_infos *infos, char *env);
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
t_command	*parser(char *line, t_infos *infos);

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
int	remove_quotes(t_lexer **lexer);


int	lexer_node(t_lexer **lst, char *line, int start, int len);
int	ft_lexer(t_lexer **lexer, char *line);
void	lexer_free(t_lexer **lexer);
void	tokenizer(t_lexer **lexer);

int ft_isquote(char quote);
int ft_ismeta(char meta);
int ft_isspecial(char c);
int double_meta(int index, char *line);

void	expanding(t_lexer **lexer, t_infos *infos);
bool	quote_status(bool quotes);
int		skip_single_quote(char *line, int index);

void	parse_lstadd_back(t_lst_redirects **lst,  t_lst_redirects *new);

int	parse_struct_command(t_lexer **lexer, t_command *command);

int	pipe_parse(t_lexer *lexer, t_command *command, t_token token);
int	here_parse(t_lexer *lexer, t_command *command, t_token token);
int	stdinn_parse(t_lexer *lexer, t_command *command, t_token token);
int	stdout_parse(t_lexer *lexer, t_command *command, t_token token);
int	append_parse(t_lexer *lexer, t_command *command, t_token token);

int	here_doc(char *end_of_file);
int	open_here_doc(char *end_of_file, char **path);

//EXECUTION BELOW
void	start_exec(t_command *commands, t_infos *infos);
#endif