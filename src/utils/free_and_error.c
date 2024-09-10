/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_and_error.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:41:04 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/06 18:14:34 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	error_msg(char *message, char c, char c2)
{
	if (!c && !c2)
		printf("%s %c%c\n", message, c, c2);
	else if (!c2)
		printf("%s `%c'\n", message, c);
	return (true);
}

static void	free_list(t_token *list)
{
	t_token	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->null == true)
		{
			free(temp);
			return ;
		}
		if (temp->str)
			free(temp->str);
		free(temp);
	}
}

// free(data->process); ??
// free(&data); ??
// free(data->list); // still necessary?
void	free_all(t_data	*data)
{
	free(data->input);
	free_list(data->list);
	data->process = 1;
	data->input = NULL;
	data->list = NULL;
}

void	free_array(char **str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
}

void	free_node(t_token *node)
{
	if (node)
	{
		free(node->str);
		free(node);
	}
}
