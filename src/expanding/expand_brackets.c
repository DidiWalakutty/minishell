/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_brackets.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: didi <didi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/14 16:18:18 by didi          #+#    #+#                 */
/*   Updated: 2024/09/20 18:16:56 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_joined(t_joined *join, char **updated_joined)
{
	if ((!join->remainder || join->remainder[0] == '\0') && \
		(!join->before || join->before[0] == '\0'))
		*updated_joined = ft_strdup("");
	else if (!join->remainder || join->remainder[0] == '\0')
		*updated_joined = ft_strdup(join->before);
	else if (!join->before || join->before[0] == '\0')
		*updated_joined = ft_strdup(join->remainder);
	else
		*updated_joined = ft_strconcat(join->before, join->remainder);
}
