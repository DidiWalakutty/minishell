/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenize_utils2.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/20 21:12:35 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/30 19:31:29 by diwalaku      ########   odam.nl         */
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

t_ad_wr	*set_process(char *str, int i)
{
	t_ad_wr	*copy;

	copy = malloc(sizeof(t_ad_wr));
	if (!copy)
		return (NULL);
	copy->str = str;
	copy->start = i;
	copy->len = i;
	copy->j = 0;
	copy->in_quote = false;
	copy->new_str = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!copy->new_str)
	{
		free(copy);
		return (NULL);
	}
	return (copy);
}
