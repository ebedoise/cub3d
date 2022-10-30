#include "cub_bonus.h"

int	__strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*__strjoin(char *s1, char *s2)
{
	int		i;
	char	*array;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	array = malloc(sizeof(char) * (__strlen(s1) + __strlen(s2) + 1));
	if (!array)
		return (NULL);
	while (s1[i])
	{
		array[i] = s1[i];
		i++;
	}
	while (s2[i - __strlen(s1)])
	{
		array[i] = s2[i - __strlen(s1)];
		i++;
	}
	array[i] = '\0';
	free(s1);
	return (array);
}

char	*__strdup(char *s1)
{
	char	*array;
	int		i;

	i = 0;
	array = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!array)
		return (NULL);
	while (s1[i])
	{
		array[i] = s1[i];
		i++;
	}
	array[i] = '\0';
	return (array);
}

char	*__strndup(char *s1, int n)
{
	char	*array;
	int		i;

	i = 0;
	array = malloc(sizeof(char) * (n + 1));
	if (!array)
		return (NULL);
	while (s1[i] && i < n)
	{
		array[i] = s1[i];
		i++;
	}
	array[i] = '\0';
	free(s1);
	return (array);
}

int	__atoi(char *str, int *i)
{
	int	res;
	int	sign;

	sign = 1;
	res = 0;
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == ' ')
		(*i)++;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign *= -1;
		(*i)++;
	}
	while (str[*i] && (str[*i] >= '0' && str[*i] <= '9'))
	{
		res = res * 10 + (str[*i] - 48);
		(*i)++;
	}
	while ((str[*i] >= 9 && str[*i] <= 13) || str[*i] == ' ')
		(*i)++;
	return (res * sign);
}
