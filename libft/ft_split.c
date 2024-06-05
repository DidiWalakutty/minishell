/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/20 16:49:05 by diwalaku      #+#    #+#                 */
/*   Updated: 2022/11/29 14:44:22 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	words_x(char const *str, char c)
{
	size_t	x;
	size_t	words;

	x = 0;
	words = 0;
	while (str[x] != '\0')
	{
		if (str[x] != c)
			words++;
		while (str[x] != '\0' && str[x] != c)
			x++;
		if (str[x] == '\0')
			return (words);
		x++;
	}
	return (words);
}

static size_t	word_len(char const *str, char c)
{
	size_t	x;

	x = 0;
	while (str[x] != '\0' && str[x] != c)
		x++;
	return (x);
}

static void	unleash(char **array, int part)
{
	while (part >= 0)
	{
		free(array[part]);
		part--;
	}
	free(array);
}

static int	arraysplitter(char const *str, char **array, char c)
{
	int	x;
	int	part;

	x = 0;
	part = 0;
	while (str[x] != '\0')
	{
		if (str[x] != c)
		{
			array[part] = ft_substr(str, x, word_len(str + x, c));
			if (array[part] == NULL)
			{
				unleash(array, part - 1);
				return (0);
			}
			part++;
			x += word_len(str + x, c);
			if (str[x] == '\0')
				break ;
		}
		x++;
	}
	return (1);
}

char	**ft_split(char const *str, char c)
{
	char	**array;

	if (!str)
		return (0);
	array = ft_calloc(sizeof(char *), words_x(str, c) + 1);
	if (!array)
		return (0);
	if (arraysplitter(str, array, c) != 1)
		return (NULL);
	return (array);
}
