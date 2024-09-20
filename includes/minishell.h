/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                       :+:    :+:             */
/*                                                     +:+                    */
/*   By: diwalaku <diwalaku@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/20 16:38:50 by diwalaku      #+#    #+#                 */
/*   Updated: 2024/09/18 22:52:26 by sreerink      ########   odam.nl         */
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
# include <termios.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

// Defining ANSI colors
//

# define SHELL_NAME "Minishell$ " // which name, colors?

typedef enum s_type			t_type;
typedef enum s_exp			t_exp;
typedef struct s_here_dol	t_h_dol;
typedef struct s_joined		t_joined;
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
	SEPARATOR,
	WORD,
	PIPE,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	REDIR_IN,		// <  in
	REDIR_OUT,		// >  out
	HERE_DOC,		// << heredoc
	APPEND,			// >> append
}	t_type;

typedef enum s_exp
{
	IS_DOLLAR,
	IS_EXIT,
	IS_PID,
}	t_exp;

typedef struct s_here_dol
{
	char	*expanded;	// expanded env-variable
	char	*env_name;	// env-name
	char	*copy;
	int		i;
	int		start_env;
	int		end_var;
	int		str_len;
	bool	brackets;	// check for brackets
	bool	no_closing_brackets;
	t_exp	exp_kind;
	// bool	quotes;		// check for quotes
	// char	quote_type;	// s_q or d_q
}	t_h_dol;

typedef struct s_joined
{
	char	*joined;
	char	*before;
	char	*remainder;
}	t_joined;

typedef struct s_expand
{
	t_token	*head;
}	t_expand;

typedef struct s_dollar
{
	char	*expanded;
	char	*env_name;
	int		i;
	int		str_len;
	int		start_env;
	int		end_var;
	bool	brackets;
	bool	no_closing_bracket;
	t_exp	exp_kind;
}	t_dollar;

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
	int			pipe_hdoc[2];
	t_redin		*next;
}	t_redin;

typedef struct s_redir_out
{
	char		*str;
	bool		append;
	t_redou		*next;
}	t_redou;

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
	ECHO_BUILTIN,
	PWD,
	ENV,
}	t_builtin;

typedef struct s_cmd
{
	pid_t		pid;
	char		*cmd;
	char		*path;
	char		**args;
	char		**env;
	t_redin		*redir_in;
	t_redou		*redir_out;
	bool		pipe_in;
	bool		pipe_out;
	t_builtin	builtin;
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
}	t_data;

//-------------------------------------------------------------------------//
//                               Functions                                 //
//-------------------------------------------------------------------------//

char	**copy_env(char **env);
char	**make_env_var(char *new_var, char *value, char **env);
char	**delete_env_var(char *del_var, char **env);
bool	replace_var_value(char *new_value, char *var_dst, char **env);
bool	add_var_value(char *new_value, char *var_dst, char **env);
bool	init_shlvl(t_data *data);

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
void	reset_joined(t_joined *join, char **updated_joined);
char	*check_joined(char *before, char *fill_in);

//-------------------------------------------------------------------------//
//                          Build Commands                                 //
//-------------------------------------------------------------------------//

t_cmd	*build_commands(t_token *nodes, t_data *data);
t_cmd	*merge_commands(t_token *tokens, t_data *data);
int		handle_redirect(t_token **token, t_cmd **command);

//-------------------------------------------------------------------------//
//                          Heredoc Expanding	                           //
//-------------------------------------------------------------------------//

char	*heredoc_expanding(char *str, t_data *data);
bool	is_heredoc_dollar(char *str, int i);
bool	is_heredoc_double(char *str, int i);
bool	is_heredoc_exit(char *str, int i);
t_h_dol	*init_here_dol(char *str);
t_h_dol	*init_here_pid(char *str);
t_h_dol	*init_here_exit(char *str, int exit);
void	set_env_and_expand(char *str, t_h_dol *info, char **env, \
		bool *expanded);
void	expand_here_pid(char *str, t_h_dol *info, bool *expanded);
void	expand_here_exit(char *str, t_h_dol *info, bool *expanded);
void	expand_heredoc_string(char *str, t_h_dol *info, bool *expanded);
void	free_cmds(t_cmd *cmd_list);

//-------------------------------------------------------------------------//
//                          Signals                                        //
//-------------------------------------------------------------------------//

bool	disable_echoctl(void);
void	enable_echoctl(void);
void	set_signals_ia_mode(void);
void	set_signals_nia_mode(void);
void	set_signals_hdoc_mode(void);
void	set_signals_hdoc_parent_mode(void);

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
int		empty_words(t_token *nodes);
int		remove_spaces(t_token *list);
void	init_redirects(t_cmd *cmd);
bool	a_redirection(t_type type);
t_cmd	*init_cmds(t_data *data);
char	**add_to_double_array(char **arguments, char *str);
bool	str_is_all_digits(char *str);

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
//                           Free - Exits                                  //
//-------------------------------------------------------------------------//

void	free_array(char **str);
bool	error_msg(char *message, char c, char c2);
void	free_all(t_data	*data);
void	free_node(t_token *node);
void	free_heredoc_info(t_h_dol *info);
void	*mem_check(void *pointer);
void	error_exit(const char *msg, int status);

//-------------------------------------------------------------------------//
//                               Testing                                   //
//                       not norminette friendly                          //
//-------------------------------------------------------------------------//

const char	*type_to_string(t_type type);
void	print_linked_list(t_token *head);
void	print_env(char **env);
void	print_commands(t_cmd *cmd);
void	print_redou(t_redou *redir);
void	print_redin(t_redin *redir);
char	*update_remainder(char *str, t_dollar *var);

//-------------------------------------------------------------------------//
//                           Execution                                     //
//-------------------------------------------------------------------------//

void	error_exit(const char *msg, int status);
int		make_processes(t_data *data);

//-------------------------------------------------------------------------//
//                           Redirecting                                   //
//-------------------------------------------------------------------------//

bool	redirect_fd(int fd, int fd_dst);
int		check_heredocs(t_data *data);
bool	check_heredocs_parent(t_redin *redir_in);
void	heredoc(t_redin *redir_in, bool redirect);

//-------------------------------------------------------------------------//
//                           Builtins                                  //
//-------------------------------------------------------------------------//

int		execute_builtin(t_cmd *cmd, t_data *data);
int		cd_builtin(t_cmd *cmd, t_data *data);
int		echo_builtin(t_cmd *cmd);
int		pwd_builtin(void);
int		export_builtin(t_cmd *cmd, t_data *data);
int		unset_builtin(t_cmd *cmd, t_data *data);
int		env_builtin(char **env);
int		exit_builtin(t_cmd *cmd, t_data *data);

#endif
