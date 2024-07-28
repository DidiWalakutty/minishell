/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strconcat.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 18:57:19 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/28 16:50:23 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strconcat(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;
	int		len_s1;
	int		len_s2;

	i = 0;
	j = 0;
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new = malloc(sizeof(char) + (len_s1 + len_s2 + 1));
	if (!new)
		return (NULL);
	while (i < len_s1)
	{
		new[i] = s1[i];
		i++;
	}
	while (j < len_s2)
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	new[i] = '\0';
	return (new);
}
