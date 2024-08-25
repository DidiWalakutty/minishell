/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   shlvl.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/08/25 22:49:38 by sreerink      #+#    #+#                 */
/*   Updated: 2024/08/25 23:17:06 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	increment_shlvl(char **env)
{
	size_t	i;
	int		shlvl_int;
	char	*shlvl_str;

	i = 0;
	while (env[i])
	{
		if (!strncmp(env[i], "SHLVL=", 6))
		{
			shlvl_int = atoi(env[i] + 6) + 1;
			shlvl_str = ft_itoa(shlvl_int);
			if (!shlvl_str)
				return (false);
			if (!replace_var_value(shlvl_str, "SHLVL=", env))
			{
				free(shlvl_str);
				return (false);
			}
			free(shlvl_str);
			return (true);
		}
		i++;
	}
	return (false);
}
