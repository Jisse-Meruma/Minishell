
#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>
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
char	*path_creation(t_infos *infos, char *command);
int		init(t_infos *infos, char **envp);

int		compare(char *s1, char *s2);

void	cmd_cd(t_infos *infos, char *input);
void	cmd_pwd(t_infos *infos);
void	cmd_env(t_infos *infos);
void	cmd_get_env(t_infos *infos, char *env);
void	cmd_get_env_pwd(t_infos *infos, char *env);
char	*cmd_get_env_char(t_infos *infos, char *env);
void	change_env_data(t_infos *infos, char *env, char *data);
int		cmd_check_env_exist(t_infos *infos, char *env);
void	cmd_unset(t_infos *infos, t_command *cmd);
void	exec_export(t_infos *infos, char *str);
void	cmd_export(t_infos *infos, t_command *cmd);
void	cmd_echo(t_command *cmd);
void	cmd_exit(t_infos *infos, char **args);
void	ft_free_lst(t_node* head);
void	not_valid_id(char *str, char *cmd);

void	mainsignal(void);
void	signal_cmd(t_infos *infos);
int		list_env(char **env, t_infos *infos);

int		ret_error(char *str, int fd, int ret);
void	void_ret_error(char *str, int fd);
void	exit_error(char *str, int fd);

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

// LEXER
int		lexer_node(t_lexer **lst, char *line, int start, int len);
int		ft_lexer(t_lexer **lexer, char *line);
void	lexer_free(t_lexer **lexer);
void	tokenizer(t_lexer **lexer);

int		ft_isquote(char quote);
int		ft_ismeta(char meta);
int		ft_isspecial(char c);
int		double_meta(int index, char *line);

// Remove/Expand the text_cmds
bool	expanding(t_lexer **lexer, t_infos *infos);
char	*search_env_var(char *line, t_infos *infos);
bool	ambiguous_redir(t_lexer	**lexer, t_lexer *node, char *str);
bool	find_env_var(char *line);
bool	quote_status(bool quotes);
int		skip_single_quote(char *line, int index);
int		env_name_lenght(char *line, int index, int i);

// parse list util
void	parse_lstadd_back(t_lst_redirects **lst,  t_lst_redirects *new);

// main parse function
int		parse_struct_command(t_lexer **lexer, t_command *command);

// all special parse
int		pipe_parse(t_lexer *lexer, t_command *command, t_token token);
int		here_parse(t_lexer *lexer, t_command *command, t_token token);
int		stdinn_parse(t_lexer *lexer, t_command *command, t_token token);
int		stdout_parse(t_lexer *lexer, t_command *command, t_token token);
int		append_parse(t_lexer *lexer, t_command *command, t_token token);

//Redirect file opening
int		here_doc(char *end_of_file, t_infos *infos);
int		here_doc_unlink_and_close(char *path, int old_fd);
int		open_here_doc(char *end_of_file, char **path);

//EXECUTION BELOW
void	start_exec(t_command *commands, t_infos *infos);
void	dup_in_out(t_command *commands, t_infos *infos);
int		dup_all(t_command *cmd, t_infos *infos, int orexit);
char	**get_envp(t_infos *infos);
int		ft_isnumber(char *str);
void	ft_2d_print(char **str);
int		ft_our_lst_size(t_node *lst);
void	exec_built(t_infos *infos, t_command *cmd);
void	if_builtins(t_command *cmd);
void	add_shlvl(t_infos *infos);
// Cleanup
void	free_cmd_struct(t_command *commands);

// Debug the write and read pipes remove afte
int		redirect_is_out(t_command *commands);
void	print_error(char *str, char *error);
void	ex_print_error(char *str, char *error, int exitnb);
void	free_infos(t_infos *infos);

#endif
