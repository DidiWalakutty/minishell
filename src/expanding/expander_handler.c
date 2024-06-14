/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_handler1.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:46:45 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/06/14 18:47:11 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void    handle_error(t_token **tokens, t_token **head, \
        t_expander *var, t_env *env)
{
	error_code_expansion(*tokens, head, var->i, env);
	
}
