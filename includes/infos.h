#ifndef INFOS_H
# define INFOS_H

#include <signal.h>
#include <sys/types.h>
#include <errno.h>

typedef struct s_node 
{
	char *name;
	char *data;
	struct s_node* next;
} t_node;

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