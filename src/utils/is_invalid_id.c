#include "minishell.h"

int check_valid_id(char *str){
    int i;

    i = 0;
	if (!str[0])
		return (0);
	if (ft_isdigit(str[0])|| str[0] == '=')
		return (0);
    while (str[i]){
        if (ft_isspace(str[i]) || \
        (str[i] >= 32 && str[i] <= 47) || \
        (str[i] >= 58 && str[i] <= 60) || \
        (str[i] >= 62 && str[i] <= 64) || \
        (str[i] >= 91 && str[i] <= 94) || \
        (str[i] == 96) || \
        (str[i] >= 123 && str[i] <= 126))
            return (0);
        if (str[i] == '=')
            return (1);
        ++i;
    }
	return (1);
}