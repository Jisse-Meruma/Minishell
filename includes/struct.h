#ifndef STRUCT_H
# define STRUCT_H

# include <stdbool.h>
typedef struct s_lexer
{
	char 			*argument;
	struct s_lexer	*next;
}	t_lexer;
	
#endif