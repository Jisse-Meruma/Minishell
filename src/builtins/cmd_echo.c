#include "minishell.h"
// #include <stdio.h>
// #include <stdbool.h>
// #include <unistd.h>

void    is_endline(char *str, bool *n)
{
    int i;

    i = 0;
    if (str[i] && str[i] == '-')
        ++i;
    while (str[i] && str[i] == 'n')
        ++i;
    if (i)
        *n = true;
}

void    echoprint(t_infos *infos, char *str)
{
    int i;
    
    i = 0;
    while (str[i])
    {
        if (str[i] == '$' && str[i + 1] && str[i + 1] == '?')
        {
            ft_putnbr_fd(infos->error, 1);
            ++i;
        }
        else
            write(1, &str[i], 1);
        ++i;
    }
}

//void	cmd_echo(char **str)
// echo is working now with str as argv skipping the first argument
void	cmd_echo(t_infos *infos, char **str)
{
    bool n;
    int i;

    n = false;
    i = 1;
    is_endline(str[i], &n);
    if (n == false)
        ++i;
    while (str[i])
    {
        echoprint(infos, str[i]);
        ++i;
        if (str[i])
            write(1, " ", 1);
    }
    if (n == true)
        write(1, "\n", 1);
    infos->error = 0;
    return ;
}

// int main(int argc, char **argv)
// {
//     if (argc > 1)
//         cmd_echo(argv);
//     return 0;
// }