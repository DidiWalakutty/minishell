/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:43:34 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/03 22:13:49 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_len(char *str, int i, char c)
{
	int	len;

	i++;
	len = 0;
	while (str[i + len])
	{
		if (c == '\'' && str[i + len] == '\'')
		{
			while (str[i + len + 1] != ' ')
			{
				len++;
				if (str[i + len] == '\'')
					return (len);
			}
			return (len);
		}
		if (c == '\"' && str[i + len] == '\"')
			return (len);
		len++;
	}
	return (len);
}

int	quote_length(char *str, char c)
{
	int	i;

	i = 0;
	if (c == '\'' || c == '\"')
	{
		while (str[i] && str[i] != c)
			i++;
		return (i);
	}
	return (i);
}

// Add 2 for the opening and closing quote, remove 2 for line
//  (we don't want to include the quotes).
// Returns i - 1, so the i in tokenize_input immediately follows
// the closing quote's position that we return.
// Should we consider "" as an empty string and add it to the node-list?
//  free line?
int	add_quote(char *str, int i, char c, t_node **list)
{
	t_node	*new;
	int		start;
	int		len;
	// int		len2;
	char	*line;
	bool	null;

	null = false;
	start = i + 1;
	// len1 = quote_length(&str[start], c) + 2;
	len = quote_len(str, i, c);
	if (len == 2)
	{
		line = "\0";
		null = true;
	}
	else
		line = ft_substr(str, start, len - 2);
	i = len + start + 1;
	new = create_node(line, EMPTY);
	if (c == '\'')
		new->type = SINGLE_QUOTE;
	else
		new->type = DOUBLE_QUOTE;
	new->null = null;
	node_to_list(list, new);
	return (i - 1);
}

// We add a token, either >> or <<.
// It the i + 1 isn't equal, it adds one token.
int	add_redir_or_pipe(char *str, int i, t_data *data, t_node **list)
{
	t_node	*new;
	char	*line;

	if (str[i + 1] == str[i])
	{
		line = ft_substr(str, i, 2);
		new = create_node(line, EMPTY);
		if (str[i] == '>')
			new->type = APPEND;
		else if (str[i] == '<')
			new->type = HERE_DOC;
		node_to_list(list, new);
		i += 2;
	}
	else
		i = add_one_token(str, i, data, list);
	return (i);
}

int	add_pipe(char *str, int i, t_node **list)
{
	char	*line;
	t_node	*new;

	line = ft_substr(str, i, 1);
	new = create_node(line, PIPE);
	node_to_list(list, new);
	i += 1;
	return (i);
}

// !in_quote toggles the value of the current in_quote 
// flag during the while-loop.
int	add_word(char *str, int i, t_node **list)
{
	t_node	*new;
	char	*line;
	int		start;
	int		len;
	bool	in_quote;

	start = i;
	len = i;
	in_quote = false;
	while (str[len] && !one_of_tokens(str[len]) && \
			!iswhitespace(str[len]))
	{
		if (str[len] == '\'' || str[len] == '\"')
			in_quote = !in_quote;
		while (str[len] && in_quote && str[len] != str[start])
			len++;
		len++;
	}
	line = ft_substr(str, start, len - start);
	new = create_node(line, WORD);
	node_to_list(list, new);
	i = len;
	return (i);
}
