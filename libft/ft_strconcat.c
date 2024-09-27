/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strconcat.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 18:57:19 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/27 19:49:54 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	copy_string(char *dest, const char *str, int *index)
{
	while (*str)
	{
		dest[*index] = *str;
		(*index)++;
		str++;
	}
}

char	*ft_strconcat(char *s1, char *s2)
{
	char	*new;
	int		len_s1;
	int		len_s2;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	new = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!new)
		return (NULL);
	copy_string(new, s1, &i);
	copy_string(new, s2, &i);
	new[i] = '\0';
	return (new);
}
