#include "minishell.h"

int ft_atoi64_overflow(const char *str, int64_t *numb)
{
    int i;
    int sign;

    i = 0;
    sign = 1;
    *numb = 0;
    if (!str)
        return 1;
    while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
           || str[i] == '\r' || str[i] == '\t' || str[i] == '\v')
        i++;
    if (str[i] == '-') 
    {
        sign = -1;
        i++;
    } 
    else if (str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9') 
    {
        int digit = str[i] - '0';
        if (*numb > INT64_MAX / 10 || (*numb == INT64_MAX / 10 && digit > INT64_MAX % 10))
        {
            if (sign == 1) 
                *numb = INT64_MAX;
            else
                *numb = INT64_MIN;
            return 1;
        }
        *numb = *numb * 10 + digit;
        i++;
    }
    *numb *= sign;
    return (0);
}

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