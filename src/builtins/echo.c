/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   echo.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/07/17 15:29:51 by sreerink      #+#    #+#                 */
/*   Updated: 2024/07/17 15:30:32 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo_builtin(const char *str, bool newline)
{
	if (newline)
		printf("%s\n", str);
	else
		printf("%s", str);
}
