/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_brackets_and_utils.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: didi <didi@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/09/14 16:18:18 by didi          #+#    #+#                 */
/*   Updated: 2024/10/01 22:00:00 by diwalaku      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_joined(t_joined *join, char **updated_joined, t_expand *info)
{
	if ((!join->remainder || join->remainder[0] == '\0') && \
		(!join->before || join->before[0] == '\0'))
	{
		*updated_joined = ft_strdup("");
		if (!*updated_joined)
			info->mal_fail = true;
	}
	else if (!join->remainder || join->remainder[0] == '\0')
	{
		*updated_joined = ft_strdup(join->before);
		if (!*updated_joined)
			info->mal_fail = true;
	}
	else if (!join->before || join->before[0] == '\0')
	{
		*updated_joined = ft_strdup(join->remainder);
		if (!*updated_joined)
			info->mal_fail = true;
	}
	else
	{
		*updated_joined = ft_strconcat(join->before, join->remainder);
		if (!*updated_joined)
			info->mal_fail = true;
	}
}

void	extract_env_variable(t_token *node, t_dollar *dol)
{
	dol->start_env = dol->i + 1;
	if (node->str[dol->start_env] == '{')
	{
		dol->brackets = true;
		dol->start_env++;
	}
	dol->end_var = dol->start_env;
	while (node->str[dol->end_var] && (is_alph_or_num(node->str[dol->end_var]) \
		|| node->str[dol->end_var] == '_'))
	{
		dol->end_var++;
		if (node->str[dol->end_var] == '$')
			break ;
	}
	if (dol->brackets == true && node->str[dol->end_var] != '}')
		dol->no_closing_bracket = true;
}

static void	remove_node(t_token **head, t_token **prev, t_token **current)
{
	if (*prev == NULL)
	{
		*head = (*current)->next;
		free_node(*current);
		*current = *head;
	}
	else
	{
		(*prev)->next = (*current)->next;
		free_node(*current);
		*current = (*prev)->next;
	}
}

void	remove_empty_words(t_token **head)
{
	t_token	*current;
	t_token	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (current->type == WORD && ft_strcmp(current->str, "") == 0)
		{
			if (prev == NULL)
				remove_node(head, &prev, &current);
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

bool	empty_words(t_token *list)
{
	int	i;

	i = 0;
	while (list)
	{
		if (list->type == WORD && ft_strcmp(list->str, "") == 0)
			i++;
		list = list->next;
	}
	if (i > 0)
		return (true);
	return (false);
}
