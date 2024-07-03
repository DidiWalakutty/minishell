/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                  :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:25:21 by marvin            #+#    #+#             */
/*   Updated: 2024/06/12 20:24:33 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void if_expandable(t_expander *var, t_token *type)
{
    if (type == SEPARATOR || type = PIPE || type = APPEND || \
        type == REDIR_IN || type == REDIR_OUT)
        var->if_expand = true;
    else if (type == HERE_DOC)
        var->if_expand = false;
}

t_expander   *init_var(t_token **tokens)
{
    t_expander *var;

    var = malloc(sizeof(t_data));
    var->head = *tokens;
    var->old_pos = 0;
    var->i = 0;
    var->if_expand = true;
    var->move_pointer = true;
}
