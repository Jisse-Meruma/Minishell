#ifndef INFOS_H
# define INFOS_H

#include <signal.h>
#include <sys/types.h>
#include <errno.h>

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
	pid_t               pid;
	char                *pwd;
	int                 error;
	struct sigaction	sa;
	pid_t               **pids;
	t_node              *head;
}	t_infos;
	

#endif