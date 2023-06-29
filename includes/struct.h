#ifndef STRUCT_H
# define STRUCT_H

# include <signal.h>
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

typedef enum s_builtins
{
	NOCMD,
	NOT_BUILT,
	BUILT,
	BUILT_PARENT,
} t_builtins;

typedef enum s_cmdnb
{
	ONE_CMD,
	FIRST_CMD,
	CMD,
	LAST_CMD,
} t_cmdnb;

typedef struct s_command
{
	char				**cmd_argv;
	t_lst_redirects		*lst_redirects;
	struct s_command	*next;
	t_builtins			cmd_is_blt;
	t_cmdnb				order;
}	t_command;

typedef int (* t_parse_meta)(t_lexer *, t_command *, t_token);

typedef enum s_env_data
{
	EMPTY,
	NO_VALUE,
	FULL,
	SIZE,
} t_env_data;

typedef struct s_node
{
	char			*name;
	char			*data;
	t_env_data		type;
	struct s_node	*next;
} t_node;

typedef struct s_glo
{
	int error;
} t_glo;

extern t_glo g_glo;

typedef struct s_infos
{
	int					read_fd;
	int					write_fd;
	int 				pipes[2];
	pid_t               pid;
	char                *pwd;
	t_node              *head;
}	t_infos;

#endif
