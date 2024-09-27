/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_and_error.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:41:04 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/27 21:47:18 by diwalaku      ########   odam.nl         */
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

void	free_list(t_token *list)
{
	t_token	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->str)
			free(temp->str);
		free(temp);
	}
}

void	reset_data(t_data *data)
{
	free(data->input);
	free_list(data->list);
	free_cmds(data->cmd_process);
	data->process = 1;
	data->input = NULL;
	data->list = NULL;
	data->cmd_process = NULL;
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
