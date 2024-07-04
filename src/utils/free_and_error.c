/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diwalaku <diwalaku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 18:41:04 by diwalaku          #+#    #+#             */
/*   Updated: 2024/07/04 15:41:27 by diwalaku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	error_msg(char *message, char c)
{
	ft_printf("%s `%c'\n", message, c);
	return (true);
}

void	free_array(char **str)
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
