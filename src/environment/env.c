/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                             :+:    :+:             */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:39:23 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/15 14:33:05 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// split on '=' and name + value?
// Copies current env. Should eventually also update ShellLevel
char	**copy_env(char **env)
{
	char	**copy;
	int		i;

	i = 0;
	while (env[i])
		i++;
	copy = ft_calloc(sizeof(char *), i + 1);
	if (!copy)
		return (NULL);
	i = 0;
	while (env[i])
	{
		copy[i] = ft_strdup(env[i]);
		if (copy[i] == NULL)
		{
			free_array(copy);
			return (copy);
		}
		i++;
	}
	return (copy);
}