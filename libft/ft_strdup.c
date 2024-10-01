/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/13 20:24:00 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/30 23:13:08 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int len)
{
	char	*copy;
	int		i;

	if (!s1)
		return (NULL);
	if (len > (int)ft_strlen(s1))
		len = (int)ft_strlen(s1);
	i = 0;
	copy = (char *)malloc(sizeof(char) * (len + 1));
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
	char	*s_copy;
	size_t	len;

	len = ft_strlen(s1) + 1;
	s_copy = malloc(sizeof(char) * len);
	if (!s_copy)
		return (0);
	ft_strlcpy(s_copy, s1, len);
	return (s_copy);
}
