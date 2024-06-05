/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 22:05:16 by marvin            #+#    #+#             */
/*   Updated: 2023/12/16 22:05:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minishell.h"

void    handle_error(t_token **tokens, t_token **head, \
        t_expander *var, t_env *env)
{
	error_code_expansion(*tokens, head, var->i, env);
	
}