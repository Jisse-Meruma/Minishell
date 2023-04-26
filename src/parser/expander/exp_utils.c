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
