/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 18:02:15 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/10/11 13:56:24 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		a;
	int		z;
	char	*string;
	char	*new;

	a = 0;
	string = (char *)s1;
	if (string[a] == '\0')
		return (ft_strdup(string + a));
	if (!set)
		return (string);
	z = ft_strlen(string) - 1;
	while (string[a] && ft_strchr(set, string[a]))
		a++;
	while (a < z && ft_strchr(set, string[z]))
		z--;
	new = ft_substr(string, a, (z - a + 1));
	return (new);
}
