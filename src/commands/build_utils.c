/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/22 18:14:21 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/23 13:12:47 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks for space-input only and
// pipe_usage.
int	not_just_spaces(t_token *nodes)
{
	int		count;
	bool	flag;
	t_token	*copy;

	count = 0;
	flag = false;
	copy = nodes;
	while (nodes)
	{
		if (nodes->type == SEPARATOR)
			flag = true;
		count++;
		nodes = nodes->next;
	}
	if (flag && count == 1)
		return (0);
	remove_spaces(copy);
	return (1);
}

static void	add_to_array(char **new_array, char **arguments, char *str)
{
	int	i;

	i = 0;
	if (arguments)
	{
		while (arguments[i])
		{
			new_array[i] = ft_strdup(arguments[i]);
			if (!new_array[i])
				free_array(new_array);
			i++;
		}
	}
	if (str)
	{
		new_array[i] = ft_strdup(str);
		if (!new_array[i])
			free_array(new_array);
		i++;
	}
	new_array[i] = NULL;
}

char	**add_to_double_array(char **arguments, char *str)
{
	int		size;
	char	**new_array;

	size = 0;
	if (!str && !arguments)
		return (NULL);
	if (!str)
		return (arguments);
	if (arguments)
	{
		while (arguments[size])
			size++;
	}
	new_array = malloc(sizeof(char *) * (size + 2));
	if (!new_array)
		return (NULL);
	add_to_array(new_array, arguments, str);
	if (arguments)
		free_array(arguments);
	return (new_array);
}
