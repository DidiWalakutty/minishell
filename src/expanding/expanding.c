/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expanding.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:36:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/06/14 18:37:24 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expander(t_token **tokens, t_data *env)
{
    t_expander  *var;
    char    *type;

    var = init_var(tokens);
    while (*tokens)
    {
        if_expandable(var, (*tokens)->type);
        if (dollar_questionmark(tokens, var) == true)
            handle_error(tokens, &(var->head), var, env);
        // single dollar
        // double dollar
                
    }
    
}

int	is_error_code(t_token **tokens, bool if_expand)
{
	if (!if_expand)
		return (1);
	if (((*tokens)->type == WORD || (*tokens)->type == DOUBLE_QUOTE)
		&& ft_strnstr((*tokens)->command, "$?", \
		ft_strlen((*tokens)->command)))
		return (0);
	return (1);
}

// Handle $ during expansion!
//
// // Should we handle $$ (is PID)
// int	add_dollar(char *str, int i, t_token **list)
// {
// 	char	*line;
// 	int		dollar_len;
// 	t_token	*new;
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
//
//
// syntax check: outfile zonder naam etc.
// ><, of >>
//
// eerst herkennen
//
// erna: parsen
// alle nodes pakken en stoppen in command frame
// args, in- en outfile (redirections)
// meerdere pipes is meerdere command frames
//
// voor of na syntax check, maar in elk geval voor het parsen checken op $