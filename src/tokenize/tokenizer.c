/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tokenizer.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:40:15 by diwalaku      #+#    #+#                 */
/*   Updated: 2023/12/05 17:04:27 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// add 2 for the opening and closing quote.
int	add_quote(char *str, int i, char c, t_node **list)
{
	int		start;
	int		len;
	char	*line;
	t_node	*new;

	start = i;
	len = quote_length(&str[start + 1], c) + 2;
	printf("len is: %i\n", len);
	if (len == 2)
		return (len + start + 1);
	else
		line = ft_substr(str, start, len);
	i = len + start + 1;
	new = create_node(line);
	if (c == '\'')
		new->type = SINGLE_QUOTE;
	else
		new->type = DOUBLE_QUOTE;
	node_to_list(list, new);
	return (i);
}

int	add_redir(char *str, int i, char c, t_node **list)
{
	char	*line;
	t_node	*new;

	if (str[i + 1] == c)
	{
		line = ft_substr(str, i, 2);
		new = create_node(line);
		if (str[i] == '>')
			new->type = APPEND;
		else if (str[i] == '<')
			new->type = HERE_DOC;
		node_to_list(list, new);
		i += 2;
	}
	else
		i = add_one_token(str, i, c, list);
	return (i);
}

int	add_pipe(char *str, int i, t_node **list)
{
	char	*line;
	t_node	*new;

	line = ft_substr(str, i, 1);
	new = create_node(line);
	new->type = PIPE;
	node_to_list(list, new);
	i += 1;
	return (i);
}

int	add_space(char *str, int i, t_node **list)
{
	char	*line;
	t_node	*new;

	line = ft_substr(str, i, 1);
	new = create_node(line);
	new->type = SPACE;
	node_to_list(list, new);
	while (iswhitespace(str[i]) == true)
		i += 1;
	return (i);
}

int	add_word(char *str, int i, t_node **list)
{
	char	*line;
	t_node	*new;
	int		start;
	int		len;	

	start = i;
	len = i;
	while (str[len] && !one_of_tokens(str[len]) && \
			!iswhitespace(str[len]))
			len++;
	line = ft_substr(str, start, len);
	new = create_node(line);
	new->type = WORD;
	node_to_list(list, new);
	i = start + len;
	return (i);
}

// Handle $ during expansion!
//
// // Should we handle $$ (is PID)
// int	add_dollar(char *str, int i, t_node **list)
// {
// 	char	*line;
// 	int		dollar_len;
// 	t_node	*new;

// 	if (str[i + 1] == '?')
// 	{
// 		line = ft_substr(str, i, 2);
// 		new = create_node(line);
// 		node_to_list(list, new);
// 		i += 2;
// 	}
// 	else
// 	{
// 		dollar_len = 1; // variable_len(&str[i + 1]);
// 		line = ft_substr(str, i, dollar_len);
// 		new = create_node(line);
// 		new->type = DOLLAR;
// 		node_to_list(list, new);
// 		i += dollar_len;
// 	}
// 	return (i);
// }


// syntax check: outfile zonder naam etc.
// ><, of >>

// eerst herkennen

// erna: parsen
// alle nodes pakken en stoppen in command frame
// args, in- en outfile (redirections)
// meerdere pipes is meerdere command frames

// voor of na syntax check, maar in elk geval voor het parsen checken op $