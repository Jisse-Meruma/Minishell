#include "minishell.h"

static int	len_with_quote(char const *line, int index, int c)
{
	int	len;

	len = 1;
	while (line[index + len] != c && line[index + len])
		len++;
	if (line[index + len] != '\0')
		return (len + 1);
	return (0);
}

int ft_isspecial(char c)
{
	if (ft_isquote(c) || ft_ismeta(c))
		return (true);
	return (false);
}

int ft_isquote(char quote)
{
	if (quote == '\'' || quote == '\"')
		return (true);
	return (false);
}

int ft_ismeta(char meta)
{
	if (meta == '>' || meta == '<' || meta == '|')
		return (true);
	return (false);
}

int double_meta(t_lexer **lexer, int index, char *line)
{
	i
}

int	ft_lexer(t_lexer **lexer, char *line)
{
	int index;
	int	len;
	int check;
	bool quote_modus;

	
	index = 0;
	quote_modus = false;
	while (line[index])
	{
		len = 0;
		while (ft_isspace(line[index]) && quote_modus == false)
			index++;
		if (!line[index])
			break ;
		while (!ft_isspace(line[index + len]))
		{
			if (ft_isquote(line[index + len]))
			{
				check = len_with_quote(line, index + len, line[index + len]);
				if (check == 0)
					return (ERROR);
				len += check;
			}
			if (ft_ismeta(line[index + len]))
			{
				if (create_node(line, index, len));
					return (ERROR);
				index += len;
				len = 0;
				check = double_meta(lexer, index, line);
				if (check == 0)
					return (ERROR);
				index += check;
			}
			len += 1;
		}
		if (create_node(line, index, len));
			return (ERROR);
		index += len;
	}
	return (SUCCES);
}