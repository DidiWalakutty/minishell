/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/21 18:48:18 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/25 11:21:55 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int x)
{
	int	count;

	count = 0;
	if (x <= 0)
	{
		x *= -1;
		count++;
	}
	while (x != 0)
	{
		x /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int i)
{
	char	*str;
	int		len;

	if (i == 0)
		return (ft_strdup("0"));
	if (i == -2147483648)
		return (ft_strdup("-2147483648"));
	len = get_len(i);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	str[len] = '\0';
	len--;
	if (i < 0)
	{
		str[0] = '-';
		i *= -1;
	}
	while (i != 0)
	{
		str[len] = (i % 10) + '0';
		len--;
		i /= 10;
	}
	return (str);
}
