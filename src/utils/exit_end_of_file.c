/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   exit_end_of_file.c                                :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/10/01 02:11:14 by sreerink      #+#    #+#                 */
/*   Updated: 2024/10/01 02:11:16 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_end_of_file(t_data *data)
{
	write(STDERR_FILENO, "exit\n", 5);
	enable_echoctl();
	error_exit(NULL, data->exit_status, data);
}
