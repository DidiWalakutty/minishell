/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 21:23:34 by diwalaku      #+#    #+#                 */
/*   Updated: 2022/11/28 19:16:34 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	x;
	size_t	strlen;
	char	*newstr;

	x = 0;
	strlen = ft_strlen(s);
	if (s == 0)
		return (0);
	if (start > strlen)
		len = 0;
	if (len > strlen - start)
		len = strlen - start;
	else if (strlen < len)
		len = strlen;
	newstr = (char *)malloc(sizeof(char) * len + 1);
	if (!newstr)
		return (0);
	while (x < len && start <= strlen)
	{
		newstr[x] = s[start];
		start++;
		x++;
	}
	newstr[x] = '\0';
	return (newstr);
}
