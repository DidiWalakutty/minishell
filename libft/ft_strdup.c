/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 20:24:00 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/21 01:35:45 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int len)
{
	char	*copy;
	int		i;

	i = 0;
	copy = (char *)malloc(sizeof(char) * ft_strlen((s1) + 1));
	if (!copy)
		return (NULL);
	while (s1[i] && i < len)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		len;
	int		i;

	if (!s1)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (*s1)
	{
		str[i++] = *s1++;
	}
	str[i] = '\0';
	return (str);
}
