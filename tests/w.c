#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

int glo;

void sigint_handler(int sig) {
    glo = 0;
    printf("sig received\n");
}

int main() {
    char *line;

    signal(SIGINT, sigint_handler);
    glo = 1;
    line = readline("Minishell$ ");
    while (line)
    {
        add_history(line);
        free(line);
        while (!glo)
        {
            printf("!glo");
        }
        glo = 1;
        line = readline("Minishell$ ");
    }
    return 0;
}