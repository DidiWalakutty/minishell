/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_checks.c                                 :+:    :+:             */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:41:12 by marvin            #+#    #+#             */
/*   Updated: 2024/06/12 20:26:00 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	dollar_questionmark(t_token **tokens t_token *var)
{
    if (var->if_expand == false)
        return (false);
    else if (((*tokens)->type = DOUBLE_QUOTE || (*tokens)->type == WORD) && \
        ft_strnstr((*tokens)->str, "$?", ft_strlen((*tokens)->str)))
        return (true);
    return (false);
}
