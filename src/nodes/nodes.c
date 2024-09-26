/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nodes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:28:16 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/26 20:19:01 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redin	*create_in_node(t_cmd *cmd, char *str, t_redir_type redir_type, \
						t_type token_type)
{
	t_redin	*new_node;

	new_node = malloc(sizeof(t_redin));
	if (!new_node)
		return (NULL);
	if (str)
	{
		new_node->str = ft_strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->heredoc = (redir_type == HEREDOC);
	new_node->quotes = (token_type == SINGLE_QUOTE || \
						token_type == DOUBLE_QUOTE);
	new_node->next = NULL;
	return (new_node);
}

t_redou	*create_out_node(t_cmd *cmd, char *str, t_redir_type redir_type)
{
	t_redou	*new_node;

	new_node = malloc(sizeof(t_redou));
	if (!new_node)
		return (NULL);
	if (str)
	{
		new_node->str = ft_strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	new_node->append = (redir_type == APPENDING);
	new_node->next = NULL;
	return (new_node);
}

t_token	*last_token(t_token *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next != NULL)
		head = head->next;
	return (head);
}

t_token	*create_node(char *str, t_type type)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	if (str)
		new_node->str = ft_strdup(str);
	else
		new_node->str = ft_strdup("");
	if (!new_node->str)
	{
		free(new_node);
		return (NULL);
	}
	new_node->type = type;
	new_node->next = NULL;
	new_node->null = false;
	return (new_node);
}

void	node_to_list(t_token **head, t_token *new)
{
	t_token	*current_token;

	if (!new)
		return ;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	current_token = last_token(*head);
	current_token->next = new;
}
