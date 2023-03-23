#include <stdio.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

int glo;

void    check_leaks(void)
{
    system("leaks a.out");
}

void sigint_handler(int sig) {
    printf("\nReceived SIGINT signal\n");
    glo = 0;
}
/**
 * @brief 
 * @param 
 * @return 
*/
int	main(void)
{
	char *line;

    atexit(check_leaks);
    signal(SIGINT, sigint_handler);
    glo = 1;
	line = readline("Minishell$ ");
	while (line)
	{
		add_history(line);
		free(line);
        while (glo)
        {
		    line = readline("Minishell$ ");
        }
        glo = 1;
	}
	return (0);
}