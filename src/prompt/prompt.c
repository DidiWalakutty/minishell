/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:39:42 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/12/05 20:28:16 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// strtrim only removes spaces from beginning, until it finds
// non-space chars.
char	*prompt(t_data *data)
{
	char	*name;

	name = readline(MINISHELL_NAME);
	data->input = ft_strtrim(name, " ");
	free(name);
	if (!data->input || data->input[0] == '\0')
		return (1);
	add_history(data->input);
	return (0);
}
		// exit_error("Couldn't create line input");
