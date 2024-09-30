/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   export_utils.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: sreerink <sreerink@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2024/09/30 02:10:35 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/30 02:16:46 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_print_env(char **env)
{
	size_t	i;

	i = 0;
	while (env && env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}

char	**export_error_msg(char *arg)
{
	write(STDERR_FILENO, "minishell: export: `", 20);
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
	return (NULL);
}
