/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/14 18:36:22 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/07/04 11:28:26 by anonymous     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expand	*init_info(t_node *list)
{
	t_expand	*info;

	info = malloc(sizeof(t_expand));
	info->head = list;
	info->i = 0;
	info->expandable = false;
	info->prev_type = WORD;
	return (info); 
}

void	expandable_type(t_expand *info, t_token type)
{
	if (type == HERE_DOC)
		info->expandable = false;
	else
		info->expandable = true;
}

void	expand_input(t_node *list, char **env)
{
	t_expand	*info;

	info = init_info(list);
	while (list)
	{
		// check tilde ~
		expandable_type(info, list->type);
		// if (is_double_dollar(list, info->expendable) == true)
		// 	set_pid(list, env, info);
		if (is_dollar(list, info->expandable) == true)
			set_dollar(list, env, info);
		else
		{
			// needs to iterate, but first check if set_dollar works properly.
			break ;
		}
	}
}

// Modifies only the types D_Q and WORD, if it's expandable.
// Frees current->str and replaces it.
// t_node	*expand_input(t_node *list, char **env)
// {
// 	t_node	*current;
// 	char	*new_string;

// 	current = list;
// 	while (current)
// 	{
// 		// Should expand $ and $$
// 		if (current->type == DOUBLE_QUOTE && is_expandable(current->str, '$') == true)
// 			handle_dollar(current, env);
// 		// Should expand $, $$ and ~
// 		else if (current->type == WORD)
// 		if (current->type == WORD)
// 		{
// 			new_string = copy_env_input(env, current->str + 1);
// 			if (new_string != NULL)
// 			{
// 				free(current->str);
// 				current->str = new_string;
// 			}
// 		}
// 		current = current->next;
// 	}
// 	return (list);
// }

// static void	handle_expandable_double(t_node *current, char **env)
// {
// 	char	*expanded_dollar;
// 	char	*new_string;
// 	int		dollar_pos;
// 	int		i;

// 	i = 0;
// 	// Length of current->str
// 	// Check length of what comes out of expanded_dollar and check if current->str is bigger or same.
// 	// HERE
// 	// Also needs to check if there's anything BEHIND the $output.
// 	dollar_pos = find_dollar_position(current->str);
// 	if (dollar_pos == -1)
// 			return ;
// 	else if (dollar_pos == 0)
// 		expanded_dollar = copy_env_input(env, current->str + 1);
// 	// HERE
// 	// strcopy two strings together? len str 1 and str2, copy in return str.
// 	expanded_dollar = copy_env_input(env, current->str + dollar_pos + 1);
// 	printf("expanded dollar is: %s\n", expanded_dollar);
// 	if (!expanded_dollar)
// 		return ;
// 	else
// 	{
// 		printf("in else statement\n");
// 		new_string = combine_string_env(current->str, expanded_dollar);
// 		free(current->str);
// 		current->str = new_string;
// 		printf("current->str in double is: %s\n", current->str);
// 	}
// }

// size_t	search_str(char *str, char *to_find)
// {
// 	size_t	i;

// 	i = 0;
// 	while (str[i] == to_find[i])
// 	{
// 		i++;
// 		if (to_find[i] == '\0')
// 			return (1);
// 	}
// 	return (0);
// }


// !!! OLD OLD OLD !!!


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