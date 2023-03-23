#include "minishell.h"
#include "struct.h"

static int	len_till_quote(char const *line, int index, int c)
{
	int	len;

	len = 1;
	while (line[index + len] != c && line[index + len])
		len++;
	if (line[index + len] != '\0')
		return (len);
	return (0);
}

static int	word_count(char const *line, int len_s1)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (i < len_s1)
	{
		while (ft_isspace(line[i]) && i < len_s1)
			i++;
		if (i == len_s1)
			return (word);
		word++;
		if (line[i] == '\"' || line[i] == '\'')
			i += len_till_quote(line, i, line[i]);
		while (!ft_isspace(line[i]) && i < len_s1)
			i++;
	}
	return (word);
}

static int	substring_len(char const *line, int len_s1, int i)
{
	int	len;

	len = 0;
	while (!ft_isspace(line[i]) && i < len_s1)
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			len += len_till_quote(line, i, line[i]);
			i += len;
			i += 1;
			continue ;
		}
		len++;
		i++;
	}
	return (len);
}

static void	ft_free(char **ptr, int words)
{
	while (words >= 0)
	{
		free(ptr[words]);
		words--;
	}
	free(ptr);
}

static int	split_creation(char const *line, char **ptr, int w_count)
{
	int	len_s1;
	int	len;
	int	words;
	int	i;

	words = 0;
	i = 0;
	len_s1 = ft_strlen(line);
	while (words < w_count)
	{
		while (ft_isspace(line[i]) && i < len_s1)
			i++;
		len = substring_len(line, len_s1, i);
		ptr[words] = ft_substr(line, i, len);
		if (!ptr[words])
			return (ft_free(ptr, words), 1);
		words++;
		i += len;
	}
	return (0);
}

char	**ft_command_split(char *line)
{
	int		len_s1;
	int		w_count;
	char	**ptr;

	len_s1 = ft_strlen(line);
	w_count = word_count(line, len_s1);
	ptr = (char **)ft_calloc(w_count + 1, sizeof(char *));
	if (!ptr)
		return (NULL);
	if (split_creation(line, ptr, w_count) == 1)
		return (NULL);
	return (ptr);
}
