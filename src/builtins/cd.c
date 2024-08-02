/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   cd.c                                              :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/07/17 15:29:31 by sreerink      #+#    #+#                 */
/*   Updated: 2024/07/17 16:04:35 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_builtin(const char *dst_directory)
{
	if (chdir(dst_directory) == -1)
	{
		write(STDERR_FILENO, "minishell: cd: ", 15);
		error_exit(dst_directory, EXIT_FAILURE);
	}
}
