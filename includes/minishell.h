/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jmeruma <jmeruma@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/31 13:18:06 by mbernede      #+#    #+#                 */
/*   Updated: 2023/09/29 12:32:41 by mbernede      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <errno.h>
# include "libft.h"
# include "struct.h"
# include <stdbool.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# define ERROR 1
# define SUCCES 0
# define ER_MLC "Malloc Error"
# define ER_CD_HOME "Celeste-shell: cd: HOME not set\n"
# define ER_CD_CURDIR "Celeste-shell: cd: error retrieving current directory:"

//BUILTINS
//arg_error_blt
void		not_valid_id(char *str, char *cmd, t_infos *infos);
void		print_error(char *str, char *error, t_infos *infos);
void		ex_print_error(char *str, char *error, int exitnb);
//cmd_cd
void		cmd_cd(t_infos *infos, char **input);
//cmd_echo
void		cmd_echo(t_command *cmd, t_infos *infos);
//cmd_env
void		cmd_env(t_infos *infos);
//cmd_exit
void		cmd_exit(t_infos *infos, char **args);
//cmd_export_d
void		show_declare(t_infos *infos, int fd);
//cmd_export
void		exec_export(t_infos *infos, char *str);
void		cmd_export(t_infos *infos, t_command *cmd);
//cmd_get_env
void		change_env_data(t_infos *infos, char *env, char *data);
int			cmd_check_env_exist(t_infos *infos, char *env);
void		cmd_get_env(t_infos *infos, char *env);
char		*cmd_get_env_char(t_infos *infos, char *env);
void		cmd_get_env_pwd(t_infos *infos, char *env);
//cmd_pwd
void		cmd_pwd(t_infos *infos);
//cmd_unset
void		cmd_unset(t_infos *infos, t_command *cmd);

//CLEANUP
//free_cmd_struct
void		free_cmd_struct(t_command *commands);

//EXECUTION
void		start_exec(t_command *commands, t_infos *infos);
bool		dup_redirects(t_command *command, t_infos *infos);
bool		blt_dup_redirects(t_command *cmd, t_infos *infos);
char		**get_envp(t_infos *infos);
int			ft_isnumber(char *str);
void		ft_2d_print(char **str);
int			ft_our_lst_size(t_node *lst);
void		exec_built(t_infos *infos, t_command *cmd);
void		if_builtins(t_command *cmd);
bool		add_shlvl(t_infos *infos);
void		fill_blt_cmdnb(t_command *cmd);
void		parent_closing(t_infos *infos, int write_fd);
bool		dup_read(t_command *command, t_infos *infos, int check);
bool		dup_write(t_command *command, t_infos *infos, int check);
int			check_read_priority(t_command *command);
int			minishell_continue(t_lst_redirects **redi, bool choice);
void		ft_read(t_command *cmd, t_infos *infos);
bool		start_heredoc(t_command *cmd, t_infos *infos, int *check, \
int priority);
bool		start_read(t_command *cmd, t_infos *infos, int *check, \
int priority);
bool		start_write(t_command *cmd, t_infos *infos, int *check);

//PARSER
t_command	*parser(char *line, t_infos *infos);
int			remove_quotes(t_lexer **lexer);
// LEXER
int			lexer_node(t_lexer **lst, char *line, int start, int len);
int			ft_lexer(t_lexer **lexer, char *line);
void		lexer_free(t_lexer **lexer);
void		tokenizer(t_lexer **lexer);
int			ft_isquote(char quote);
int			ft_ismeta(char meta);
int			ft_isspecial(char c);
int			double_meta(int index, char *line);
// Remove/Expand the text_cmds
bool		expanding(t_lexer **lexer, t_infos *infos);
char		*search_env_var(char *line, t_infos *infos, int index);
bool		ambiguous_redir(t_lexer	**lexer, t_lexer *node, char *str);
bool		find_env_var(char *line);
bool		quote_status(bool quotes);
int			skip_single_quote(char *line, int index);
int			env_name_lenght(char *line, int index, int i);
// parse list util
void		parse_lstadd_back(t_lst_redirects **lst, t_lst_redirects *new);
// main parse function
int			parse_struct_command(t_lexer **lexer, t_command *command);
// all special parse
int			pipe_parse(t_lexer *lexer, t_command *command, t_token token);
int			here_parse(t_lexer *lexer, t_command *command, t_token token);
int			stdinn_parse(t_lexer *lexer, t_command *command, t_token token);
int			stdout_parse(t_lexer *lexer, t_command *command, t_token token);
int			append_parse(t_lexer *lexer, t_command *command, t_token token);

//OTHERS
char		*path_creation(t_infos *infos, char *command);
int			init(t_infos *infos, char **envp);
int			compare(char *s1, char *s2);
void		ft_free_lst(t_node *head);
void		mainsignal(int mode);
int			list_env(char **env, t_infos *infos);
int			ret_error(char *str, int fd, int ret);
void		void_ret_error(char *str, int fd, t_infos *infos);
void		exit_error(char *str, int fd, t_infos *infos);
void		set_error(t_infos *infos, int err);

//Redirect file opening
int			here_doc(char *end_of_file, t_infos *infos);
int			here_doc_unlink_and_close(char *path, int old_fd);
int			open_here_doc(char *end_of_file, char **path);

// Debug the write and read pipes remove after
void		minishell_perror(char *str);
void		free_infos(t_infos *infos);
char		**ft_split_first(char *str, char c);
int			check_valid_id(char *str);
int			ft_atoi64_overflow(const char *str, int64_t *numb);
int			ft_isnumber64(char *str);
void		fix_cmd(t_command *cmd);

#endif
