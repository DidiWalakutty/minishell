/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_and_errors.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:41:04 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/06/14 18:41:47 by diwalaku      ########   odam.nl         */
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
const char *type_to_string(t_token type) 
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
