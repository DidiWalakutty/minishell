/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   nodes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:28:16 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/10 15:18:07 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redin	*create_in_node(t_cmd *cmd, char *str, t_redir_type redir_type, \
							t_type token_type)
{
	t_redin	*new_node;

	new_node = mem_check(malloc(sizeof(t_redin)));
	if (str)
		new_node->str = ft_strdup(str);
	if (!new_node->str)
		return (NULL);
	if (redir_type == HEREDOC)
		new_node->heredoc = true;
	else
		new_node->heredoc = false;
	if (token_type == SINGLE_QUOTE || token_type == DOUBLE_QUOTE)
		new_node->quotes = true;
	else
		new_node->quotes = false;
	new_node->next = NULL;
	return (new_node);
}

t_redou	*create_out_node(t_cmd *cmd, char *str, t_redir_type redir_type)
{
	t_redou	*new_node;

	new_node = mem_check(malloc(sizeof(t_redou)));
	if (str)
		new_node->str = ft_strdup(str);
	if (!new_node->str)
		return (NULL);
	if (redir_type == APPENDING)
		new_node->append = true;
	else
		new_node->append = false;
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

	new_node = mem_check(malloc(sizeof(t_token)));
	if (str)
		new_node->str = str;
	else
		new_node->str = ft_strdup("");
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
