#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>

typedef enum s_token
{
	PIPE,
	HERE_DOC,
	STDINN_FILE,
	STDOUT_FILE,
	APPEND_FILE,
	TEXT_TOKEN,
}	t_token;

typedef struct s_lexer
{
	char 			*argument;
	t_token			token;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_lst_redirects
{
	char					*filename;
	t_token					token;
	struct s_lst_redirects	*next;
}	t_lst_redirects;

typedef struct s_redirects
{
	t_lst_redirects	*lst_redirects;
}	t_redirects;

typedef enum s_builtins
{
	NOT_BUILT,
	BUILT,
	BUILT_PARENT,
} t_builtins;

typedef struct s_command
{
	char				**cmd_argv;
	t_builtins			cmd_is_blt;
	t_redirects 		redirects;
	struct s_command	*next;
}	t_command;

typedef int (* t_parse_meta)(t_lexer *, t_command *, t_token);

#endif