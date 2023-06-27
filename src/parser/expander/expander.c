#include "minishell.h"

char	*env_strjoin(char *line, char *env_expand, char *begin, int total)
{
	char	*new_line;
	char	*end_of_line;

	new_line = ft_strjoin_free(begin, env_expand);
	if (!new_line)
		return (NULL);
	end_of_line = ft_substr(line, total, ft_strlen(line) - total);
	new_line = ft_strjoin_free(new_line, end_of_line);
	free(end_of_line);
	return (new_line);
}

char	*env_creation(char *line, t_infos *infos, int index, int *len)
{
	char	*env;
	char	*begin;
	char	*new_line;
	char	*env_expand;
	int		i;

	begin = ft_substr(line, 0, index);
	index++;
	i = env_name_lenght(line, index, *len);
	env = ft_substr(line, index, i);
	if (!env || !begin)
		return (free(env),  NULL);
	if (!ft_strncmp(env, "?", 2))
		env_expand = ft_itoa(g_glo.error);
	else
		env_expand = cmd_get_env_char(infos, env);
	new_line = env_strjoin(line, env_expand, begin, index + i);
	if (env_expand)
		*len = ft_strlen(env_expand);
	free(env);
	return (new_line);
}

char	*search_env_var(char *line, t_infos *infos)
{
	int		index;
	bool	quotes;
	int		position;

	index = 0;
	quotes = false;
	while (line[index])
	{
		position = 0;
		if (line[index] == '\"')
			quotes = quote_status(quotes);
		else if (line[index] == '\'' && quotes == false)
			index = skip_single_quote(line, index + 1);
		else if (line[index] == '$')
		{
			line = env_creation(line, infos, index, &position);
			if (!line)
				return (NULL);
			index += position - 1;
		}
		index++;
	}
	return (line);
}

bool	find_env_var(char *line)
{
	int		index;
	bool	check;

	index = 0;
	check = true;
	while (line[index])
	{
		if (line[index] == '$')
			check = false;
		index++;
	}
	return (check);
}

bool	expanding(t_lexer **lexer, t_infos *infos)
{
	t_lexer	*node;
	char	*string_free;

	node = *lexer;
	while (node != NULL)
	{
		if (node->token != TEXT_TOKEN || find_env_var(node->argument))
		{
			node = node->next;
			continue ;
		}
		string_free = node->argument;
		node->argument = search_env_var(node->argument, infos);
		if(node->argument == NULL)
			return (ERROR);
		if(ft_strlen(node->argument) == 0)
		{
			if (ambiguous_redir(lexer, node, string_free))
				return (ERROR);
		}
		if (node->argument != string_free)
			free(string_free);
		node = node->next;
	}
	return (SUCCES);
}
