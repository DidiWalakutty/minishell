/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   echo.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/04 18:47:51 by sreerink      #+#    #+#                 */
/*   Updated: 2024/08/04 21:53:20 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	is_echo_n_flag(char *str)
{
	size_t	i;

	i = 1;
	if (str[0] != '-')
		return (false);
	while (str[i] == 'n')
	{
		i++;
		if (str[i] == '\0')
			return (true);
	}
	return (false);
}

void	echo_builtin(t_cmd *cmd)
{
	size_t	i;
	bool	newline;

	i = 1;
	newline = true;
	while (cmd->args[i] && is_echo_n_flag(cmd->args[i]))
	{
		newline = false;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		i++;
	}
	if (newline)
		printf("\n");
}
