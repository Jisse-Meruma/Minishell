#include <stdio.h>
#include <stdlib.h>

static char	*creation(char const *s, unsigned int start, size_t len);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = strlen(s);
	if (i < start)
		return (strdup(""));
	ptr = creation(s, start, len);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
	{
		ptr[i] = s[start];
		i++;
		start++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static char	*creation(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	while (s[start] && i < len)
	{
		start++;
		i++;
	}
	ptr = (char *)malloc(i + 1);
	return (ptr);
}

char **ft_split_first(char *str, char c)
{
	int i;
	char **str2d;
	int end;

	i = 0;
	while (str[i] && str[i] != c)
		++i;
	if (i != strlen(str))
		end = 2;
	else
		end = 1;
	str2d = (char **)calloc(end + 1, sizeof(char *));
	str2d[end] = NULL;
	if (end == 1)
	{
		str2d[0] = strdup(str);
		return (str2d);
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			str2d[0] = ft_substr(str, 0, i);
			++i;
			break;
		}
		++i;
	}
	if (str[i] && str[i] == c)
		++i;
	if (strlen(str) != i)
		str2d[1] = ft_substr(str, i, (strlen(str) - i));
	return (str2d);
}

int main()
{
	char **strr;
	int i;

	i = -1;
	strr = ft_split_first("bonjour je suis la phrase", 'z');
	while(strr[++i])
		printf("%s", strr[i]);
	return 0;
}