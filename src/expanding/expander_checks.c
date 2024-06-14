/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_checks1.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:46:48 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/06/14 18:46:58 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

bool	dollar_questionmark(t_token **tokens t_token *var)
{
    if (var->if_expand == false)
        return (false);
    else if (((*tokens)->type = DOUBLE_QUOTE || (*tokens)->type == WORD) && \
        ft_strnstr((*tokens)->str, "$?", ft_strlen((*tokens)->str)))
        return (true);
    return (false);
}
