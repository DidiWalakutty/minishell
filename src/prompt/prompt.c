/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:39:42 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/06/05 18:49:09 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prompts the Shell Name when running our Minishell 
// + adds history where unnecessary whitespace is trimmed.
// strtrim only removes spaces from beginning, until it finds
// non-space chars. 
// TODO: Check for leaks in strtrim.
char	*prompt_shellname(t_data *data)
{
	char	*name;

	name = readline(SHELL_NAME);
	data->input = ft_strtrim(name, " ");
	free(name);
	if (!data->input || data->input[0] == '\0')
		return (NULL);
	add_history(data->input);
	return (0);
}
