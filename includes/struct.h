#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>

typedef struct s_lexer
{
	char 			*argument;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_lst_redirects
{
	char					*filename;
	struct s_lst_redirects	*next;
}	t_lst_redirects;

typedef struct s_redirects
{
	t_lst_redirects	*lst_append;
	t_lst_redirects	*lst_heredoc;
	t_lst_redirects	*lst_redirect_out;
	t_lst_redirects	*lst_redirect_inn;
}	t_redirects;

typedef struct s_command
{
	char				**cmd_argv;
	t_redirects 		redirects;
	struct s_command	*next;
}	t_command;

typedef int (* t_parse_meta)(t_lexer *, t_command *);

typedef enum s_token
{
	PIPE,
	HERE_DOC,
	STDINN_FILE,
	STDOUT_FILE,
	APPEND_FILE,
}	t_token;
#endif