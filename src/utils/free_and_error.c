/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_and_error.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:41:04 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/22 21:51:32 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	error_msg(char *message, char c, char c2)
{
	if (!c && !c2)
		printf("%s %c%c\n", message, c, c2);
	else if (!c2)
		printf("%s `%c'\n", message, c);
	else
		printf("%s `%c%c'\n", message, c, c2);
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

// to printf check type
const char	*type_to_string(t_type type)
{
	switch(type)
	{
		case EMPTY: return "EMPTY";
		case SEPARATOR: return "SPACE";
		case WORD: return "WORD";
		case PIPE: return "PIPE";
		case REDIR_IN: return "REDIR_IN";
		case REDIR_OUT: return "REDIR_OUT";
		case HERE_DOC: return "HERE_DOC";
		case APPEND: return "APPEND";
		case DOUBLE_QUOTE: return "DOUBLE_QUOTE";
		case SINGLE_QUOTE: return "SINGLE_QUOTE";
		case DOLLAR: return "DOLLAR";
		default: return "UNKNOWN";
	}
}

void	print_linked_list(t_token *head)
{
	int i = 1;
	while (head != NULL)
	{
		printf("Node %i is: %s - type is: %s \n", i, head->str, type_to_string(head->type));
		head = head->next;
		i++;
	}
	printf("\n");
}

void	print_env(char **env)
{
	int	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
