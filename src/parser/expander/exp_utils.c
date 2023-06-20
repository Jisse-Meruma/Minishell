#include "minishell.h"

bool	quote_status(bool quotes)
{
	if (quotes == true)
		quotes = false;
	else
		quotes = true;
	return (quotes);
}

int	skip_single_quote(char *line, int index)
{
	while (line[index] != '\'' && line[index])
		index++;
	return (index);
}

int	env_name_lenght(char *line, int index, int i)
{
	while (line[index + i])
	{
		if (line[index + i] == '\"' || line[index + i] == '$'\
				|| line[index + i] == '\'' || ft_isspace(line[index + i]))
			break ;
		i++;
	}
	return (i);
}
