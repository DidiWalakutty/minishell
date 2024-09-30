/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:43:34 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/30 20:17:57 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_quote(char *str, int i, char c, t_token **list)
{
	t_token	*new;
	int		len;
	char	*line;
	bool	null;

	null = false;
	len = quote_length(&str[i + 1], c) + 2;
	if (len == 2)
	{
		line = NULL;
		null = true;
	}
	else
	{
		line = ft_substr(str, i + 1, len - 2);
		if (!line)
			return (-1);
	}
	new = create_node(line, EMPTY);
	if (!new)
		return (free(line), -1);
	if (!null)
		free(line);
	continue_add_to_quote(new, list, c, null);
	return (len + i);
}

int	add_redir_or_pipe(char *str, int i, t_data *data, t_token **list)
{
	t_token	*new;
	char	*line;

	if (str[i + 1] == str[i] && (str[i] == '<' || str[i] == '>'))
	{
		line = ft_substr(str, i, 2);
		if (!line)
			return (-1);
		new = create_node(line, EMPTY);
		free(line);
		if (!new)
			return (-1);
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

int	add_pipe(char *str, int i, t_token **list)
{
	char	*line;
	t_token	*new;

	line = ft_substr(str, i, 1);
	new = create_node(line, PIPE);
	node_to_list(list, new);
	free(line);
	i += 1;
	return (i);
}

int	add_space(char *str, int i, t_token **list)
{
	t_token	*new;
	char	*line;

	line = ft_strdup(" ");
	if (!line)
		return (-1);
	new = create_node(line, SEPARATOR);
	free(line);
	if (!new)
		return (-1);
	node_to_list(list, new);
	while (iswhitespace(str[i]))
		i++;
	return (i);
}
