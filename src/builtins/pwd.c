/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   pwd.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/07/17 16:18:10 by sreerink      #+#    #+#                 */
/*   Updated: 2024/07/17 16:38:03 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd_builtin(void)
{
	char	buffer[PATH_MAX + 1];

	if (!getcwd(buffer, PATH_MAX + 1))
		error_exit("pwd", EXIT_FAILURE);
	printf("%s\n", buffer);
}
