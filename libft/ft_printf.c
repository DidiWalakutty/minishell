/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/30 19:05:35 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/12/08 15:34:30 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	convert(va_list arg, const char frmt)
{
	int	length;

	length = 0;
	if (frmt == 'c')
		length = print_char(va_arg(arg, int));
	else if (frmt == '%')
		length = print_char('%');
	else if (frmt == 's')
		length = print_str(va_arg(arg, char *));
	else if (frmt == 'p')
		length = print_pointer(va_arg(arg, unsigned long));
	else if (frmt == 'd' || frmt == 'i')
		length = print_nbr(va_arg(arg, int));
	else if (frmt == 'u')
		length = print_uns_dec(va_arg(arg, unsigned int));
	else if (frmt == 'x')
		length = print_lowerhex(va_arg(arg, unsigned int));
	else if (frmt == 'X')
		length = print_upperhex(va_arg(arg, unsigned int));
	return (length);
}

int	ft_printf(const char *frmt, ...)
{
	va_list	arg;
	int		i;
	int		value;

	va_start(arg, frmt);
	i = 0;
	value = 0;
	while (frmt[i])
	{
		if (frmt[i] == '%' && frmt[i + 1])
		{
			i++;
			value += convert(arg, frmt[i]);
		}
		else if (frmt[i] && frmt[i] != '%')
			value += print_char(frmt[i]);
		i++;
	}
	va_end(arg);
	return (value);
}
