#include "cub.h"

int	__is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	n_words(char *str, char *charset)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (str[i])
	{
		if (!__is_charset(str[i], charset))
			words++;
		while (!__is_charset(str[i], charset) && str[i])
			i++;
		i++;
	}
	return (words);
}

int	len_word(char *str, char *charset)
{
	int	i;

	i = 0;
	while (!__is_charset(str[i], charset) && str[i])
		i++;
	return (i);
}

char	*__str_n_dup(char *src, char n)
{
	int		i;
	char	*array;

	i = 0;
	array = malloc(sizeof(char) * n + 1);
	if (!array)
		return (NULL);
	while (src[i] && i < n)
	{
		array[i] = src[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}

char	**__split(char *str, char *charset)
{
	char	**array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	array = malloc(sizeof(char *) * n_words(str, charset) + 1);
	if (!array)
		return (NULL);
	while (str[i])
	{
		if (__is_charset(str[i], charset))
			i++;
		else
		{
			array[j] = __str_n_dup(str + i, len_word(str + i, charset));
			j++;
			while (!__is_charset(str[i], charset) && str[i])
				i++;
		}
	}
	array[j] = 0;
	return (array);
}
