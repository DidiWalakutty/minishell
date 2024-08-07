/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pwd.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/07/17 16:18:10 by sreerink      #+#    #+#                 */
/*   Updated: 2024/08/07 17:01:41 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd_builtin(void)
{
	char	buffer[PATH_MAX + 1];

	if (!getcwd(buffer, PATH_MAX + 1))
	{
		perror("minishell: pwd");
		return (EXIT_FAILURE);
	}
	printf("%s\n", buffer);
	return (EXIT_SUCCESS);
}
