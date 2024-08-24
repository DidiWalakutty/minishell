/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   str_utils.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/24 22:58:09 by sreerink      #+#    #+#                 */
/*   Updated: 2024/08/24 23:01:02 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	str_is_all_digits(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
