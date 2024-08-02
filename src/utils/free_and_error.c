/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_and_error.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:41:04 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/02 18:45:28 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	error_msg(char *message, char c)
{
	ft_printf("%s `%c'\n", message, c);
	return (true);
}

static void	free_list(t_node *list)
{
	t_node	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		free(temp->str);
		free(temp);
	}
}

// free(data->process); ??
// free(&data); ??
void	free_all(t_data	*data)
{
	free(data->input);
	free_list(data->list);
	// free(data->list); // still necessary?
	data->input = NULL;
	data->list = NULL;
}

int	free_dollarvar(t_dollar *var)
{
	if (var->env_name)
		free(var->env_name);
	if (var->expanded)
		free(var->expanded);
	free(var);
	return (1);
}

void	free_env_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

// to printf check type
const char	*type_to_string(t_token type)
{
	switch(type)
	{
		case EMPTY: return "EMPTY";
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

void	print_linked_list(t_node *head)
{
	int i = 1;
	while (head != NULL)
	{
		printf("Node %i is: %s - type is: %s \n", i, head->str, type_to_string(head->type));
		// if (i >= 2)
		// 	printf("Previous node %i is: %s - type is: %s \n", i - 1, head->previous->str, type_to_string(head->previous->type));
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
