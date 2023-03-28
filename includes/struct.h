#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>

typedef enum s_tokens
{
	REDIRECT_IN,
	REDIRECT_OUT,
	HERE_DOC,
	REDIRECT_OUT_APP,
	PIPE,
	COMMAND,
	ARGUMENT,
}	t_tokens;

typedef struct s_arg
{
	char 			*argument;
	t_tokens		token;
	struct s_arg	*next;
}	t_arg;
	
#endif