/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_heredocs.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: sreerink <sreerink@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/08 19:46:52 by sreerink      #+#    #+#                 */
/*   Updated: 2024/09/12 18:03:50 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	check_heredocs(t_redin *redir_in)
{
	while (redir_in)
	{
		if (redir_in->heredoc && !redir_in->next)
		{
			if (!heredoc(redir_in, true))
				return (false);
		}
		else if (redir_in->heredoc)
		{
			if (!heredoc(redir_in, false))
				return (false);
		}
		redir_in = redir_in->next;
	}
	return (true);
}
