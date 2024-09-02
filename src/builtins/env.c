/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   env.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/25 22:24:08 by sreerink      #+#    #+#                 */
/*   Updated: 2024/08/26 22:10:39 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_builtin(char **env)
{
	size_t	i;

	i = 0;
	if (!env)
		return (EXIT_SUCCESS);
	while (env[i])
	{
		//printf("i = %zu\n", i);
		printf("%s\n", env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
