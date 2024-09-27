/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_utils2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/20 21:12:35 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/27 21:49:43 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	continue_add_to_quote(t_token *new, t_token **list, char c, bool null)
{
	if (c == '\'')
		new->type = SINGLE_QUOTE;
	else
		new->type = DOUBLE_QUOTE;
	new->null = null;
	node_to_list(list, new);
}

int	continue_add_to_word(char *str, int start, int len, t_token **list)
{
	char	*line;
	t_token	*new;

	line = ft_substr(str, start, len - start);
	if (!line)
		return (-1);
	new = create_node(line, WORD);
	free(line);
	if (!new)
		return (-1);
	node_to_list(list, new);
	return (len);
}
