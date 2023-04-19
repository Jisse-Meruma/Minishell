#include "minishell.h"

static int	len_with_quote(char const *line, int index, int c)
{
	int	len;

	len = 1;
	while (line[index + len] != c && line[index + len])
		len++;
	if (line[index + len] != '\0')
		return (len);
	return (0);
}

int	skip_spaces(char *line,	int index)
{
	while (ft_isspace(line[index]))
		index++;
	return (index);
}

int	quotes(char *line, int index, int len, int *check)
{
	if (ft_isquote(line[index + len]))
	{
		*check = len_with_quote(line, index + len, line[index + len]);
		if (*check == 0)
			return (false);
		len += *check;
	}
	return (len);
}

int	line_creation(t_lexer **lexer, char *line, int *index, int *len)
{		
	int	check;

	while (!ft_isspace(line[*index + *len]) && line[*index + *len])
	{
		check = 1;
		*len = quotes(line, *index, *len, &check);
		if (check == 0)
			return (false);
		if (ft_ismeta(line[*index + *len]))
		{
			if (*len != 0)
			{
				if (lexer_node(lexer, line, *index, *len))
					return (false);
			}
			*index += *len;
			*len = double_meta(*index, line);
			if (*len == 0)
				return (false);
			return (true);
		}
		*len += 1;
	}
	return (true);
}

int	ft_lexer(t_lexer **lexer, char *line)
{
	int	len;
	int	index;
	int	check;

	index = 0;
	while (line[index])
	{
		len = 0;
		index = skip_spaces(line, index);
		if (!line[index])
			return (SUCCES);
		check = line_creation(lexer, line, &index, &len);
		if (check == 0)
			return (ERROR);
		if (line[index] && check == 1)
		{
			if (lexer_node(lexer, line, index, len))
				return (ERROR);
		}
		index += len;
	}
	return (SUCCES);
}
