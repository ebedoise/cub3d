/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: embedois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 15:26:53 by embedois          #+#    #+#             */
/*   Updated: 2023/02/08 15:26:58 by embedois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*__subsub(void)
{
	char	*array;

	array = malloc(sizeof(char));
	if (!array)
		return (NULL);
	array[0] = '\0';
	return (array);
}

char	*__substr(char *s, int start, int len)
{
	char	*array;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (len > __strlen(s) - start)
		len = __strlen(s) - start;
	if (start > __strlen(s))
	{
		array = __subsub();
		return (array);
	}
	array = malloc(sizeof(char) * (len + 1));
	if (!array)
		return (NULL);
	while (s[start + i] && i < len)
	{
		array[i] = s[start + i];
		i++;
	}
	array[i] = '\0';
	return (array);
}

int	len_word(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	n_words(char *s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			i += len_word(s + i, c);
			words++;
		}
	}
	return (words);
}

char	**__split(char *s, char c)
{
	char	**array;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	array = malloc(sizeof(char *) * (n_words(s, c) + 1));
	if (!array)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			array[j++] = __substr(s, i, len_word(s + i, c));
			if (!array[j - 1])
				return (__free(array, j - 1));
			i += len_word(s + i, c);
		}
	}
	array[j] = 0;
	return (array);
}
