/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:38:50 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/08/03 23:56:21 by sreerink      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <linux/limits.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>

// Defining ANSI colors
//

# define SHELL_NAME "Minishell$ " // which name, colors?

typedef enum s_type			t_type;
typedef struct s_list		t_list;
typedef struct s_redir		t_redir;
typedef struct s_cmd		t_cmd;
typedef struct s_expand		t_expand;
typedef struct s_redir_in	t_redin;
typedef struct s_redir_out	t_redou;
typedef struct s_token		t_token;
typedef struct s_data		t_data;

typedef enum s_type
{
	EMPTY,
	SEPARATOR,		// spaces, ' ' used for parsing only.
	WORD,			// Word
	PIPE,			// |  pipe
	REDIR_IN,		// <  in
	REDIR_OUT,		// >  out
	HERE_DOC,		// << heredoc
	APPEND,			// >> append
	DOUBLE_QUOTE,	// "  double qyote = expandable
	SINGLE_QUOTE,	// '  single quote
}	t_type;

typedef struct s_expand
{
	t_token	*head;
}	t_expand;

typedef struct s_dollar
{
	char	*expanded;
	char	*env_name;
	int		i;					// Position in string.
	int		str_len;			// Length of full node->str.
	int		start_env;			// Position after $ and/or ${.
	int		end_var;			// Position where env-name ends.
	bool	brackets;			// In case of ${}
}	t_dollar;

// word: 	a pointer to the string stored in a node
// len: 	the content length
// type: 	the content token
typedef enum s_builtin
{
	NO_BUILTIN,
	CD,
	EXPORT,
	UNSET,
	EXIT,
	ECHO,
	PWD,
	ENV,
}	t_builtin;

typedef struct s_cmd_var
{
	char	*command;
	char	**arguments;
}	t_cmd_v;

typedef enum s_redir_type
{
	UNCLEAR,
	RED_IN,
	RED_OUT,
	HEREDOC,
	APPENDING,
}	t_redir_type;

typedef struct s_redir_in
{
	char		*str;
	bool		heredoc;
	bool		quotes;
	t_redin		*next;
}	t_redin;

typedef struct s_redir_out
{
	char		*str;
	bool		append;
	t_redou		*next;
}	t_redou;

typedef struct s_cmd
{
	char		*command;
	char		**args;
	char		**env;
	t_type		type;
	t_redin		*redir_in;
	t_redou		*redir_out;
	t_cmd		*next;
}	t_cmd;

typedef struct s_token
{
	char	*str;
	t_type	type;
	t_token	*next;
	bool	null;	
}	t_token;

typedef struct s_data
{
	char	*input;
	char	**env;
	t_token	*list;
	t_type	*token;
	t_cmd	*cmd_process;
	size_t	process;
	int		exit_status;
	char	*home;
	int		shlvl;
}	t_data;

//-------------------------------------------------------------------------//
//                               Functions                                 //
//-------------------------------------------------------------------------//

// Environment and paths;
char	**copy_env(char **env);

//-------------------------------------------------------------------------//
//                               Tokenizer                                 //
//-------------------------------------------------------------------------//

int		tokenize_and_expand(t_data *data);
t_token	*tokenize_input(t_data *data, char *str);
int		add_quote(char *str, int i, char c, t_token **list);
int		add_space(char *str, int i, t_token **list);
int		add_redir_or_pipe(char *str, int i, t_data *data, t_token **list);
int		add_one_token(char *str, int i, t_data *data, t_token **list);
int		add_word(char *str, int i, t_token **list);

//-------------------------------------------------------------------------//
//                               Expander                                  //
//-------------------------------------------------------------------------//

void	expand_input(t_data *data, t_token *node, char **env);
bool	is_dollar(t_token *node, bool heredoc);
int		set_dollar(t_token *node, char **env, t_expand *info);
bool	is_exit_status(t_token *node, bool heredoc);
int		set_exit_status(t_data *data, t_token *node, t_expand *info);
bool	is_double_dollar(t_token *node, bool heredoc);
int		set_pid(t_token *node, t_expand *info);
bool	quote_type_present(t_token *node);
int		concatenate_quotes(t_token *node);

//-------------------------------------------------------------------------//
//                          Build Commands                                 //
//-------------------------------------------------------------------------//

t_cmd	*build_commands(t_token *nodes, t_data *data);
t_cmd	*merge_commands(t_token *tokens, t_data *data);
void	set_command(t_token **token, t_cmd **commands, t_cmd_v **var);
int		handle_redirect(t_token **token, t_cmd **command);

//-------------------------------------------------------------------------//
//                             Utils	                                   //
//-------------------------------------------------------------------------//

bool	check_syntax_errors(char *str);
bool	all_quotes_closed(char *str);
bool	skip_quotedstring(char *str, int *i);
void	skip_to_token(char *str, int *i);
void	skip_whitespace(char *str, int *i);
bool	check_start(char *str, int *j, bool *error_found);
int		quote_length(char *str, char c);
bool	one_of_tokens(char c);
bool	check_null(t_token **node);
char	*copy_env_input(char **env, char *to_find);
int		if_valid_char(char c);
void	expand_node(t_token *node, t_dollar *var);
bool	quote_type_present(t_token *node);
int		concatenate_quotes(t_token *list);
int		not_just_spaces(t_token *nodes);
int		remove_spaces(t_token *list);
void	init_redirects(t_cmd *cmd);
bool	a_redirection(t_type type);
t_cmd	*init_cmds(void);
char	**add_to_double_array(char **arguments, char *str);

//-------------------------------------------------------------------------//
//                             Nodes	                                   //
//-------------------------------------------------------------------------//

void	node_to_list(t_token **list, t_token *new);
int		create_redir_out(t_cmd *cmd, char *result, t_redir_type redir_type);
t_token	*create_node(char *str, t_type type);
t_redou	*create_out_node(t_cmd *cmd, char *str, t_redir_type redir_type);
t_token	*last_token(t_token *list);
t_redin	*create_in_node(t_cmd *cmd, char *str, t_redir_type redir_type, \
			t_type token_type);
int		create_redir_in(t_cmd *cmd, char *result, t_redir_type redir_type, \
						t_type token_type);

//-------------------------------------------------------------------------//
//                             Free	                                       //
//-------------------------------------------------------------------------//

void	free_array(char **str);
bool	error_msg(char *message, char c, char c2);
void	free_all(t_data	*data);
void	free_node(t_token *node);
void	*mem_check(void *pointer);


//-------------------------------------------------------------------------//
//                               Testing                                   //
//                       not nourminette friendly                          //
//-------------------------------------------------------------------------//

const char	*type_to_string(t_type type);
void	print_linked_list(t_token *head);
void	print_env(char **env);
void	print_commands(t_cmd *cmd);
void	print_redou(t_redou *redir);
void	print_redin(t_redin *redir);

#endif
