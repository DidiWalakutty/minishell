NAME	=	minishell

# Libraries and Headers
LIBFT	= ./libft/libft.a
HEADERS	= -I includes -I libft/HEADERS

# Configuration
CC		= 	cc
CFLAGS	=	-g3
# CFLAGS	+= -fsanitize=address -g
RM 		= rm -rf

# Readline files
LFLAGS	= -L $(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline
IFLAGS	= -I includes -I $(HOME)/.brew/Cellar/readline/8.2.1/include

# Source Files
SRC =	./src/main.c \
				./src/environment/copy_env.c \
				./src/environment/modify_env.c \
				./src/environment/shlvl.c \
				./src/nodes/nodes.c \
				./src/tokenize/lexer.c \
				./src/tokenize/quotes.c \
				./src/tokenize/tokenize_utils.c \
				./src/tokenize/tokenize_utils2.c \
				./src/tokenize/tokenizer.c \
				./src/tokenize/tokenize_word.c \
				./src/expanding/expander.c \
				./src/expanding/expand_dollar.c \
				./src/expanding/expand_double_dollar.c \
				./src/expanding/expand_exit_and_empty.c \
				./src/expanding/quote_concatenation.c \
				./src/expanding/expand_brackets_and_utils.c \
				./src/expanding/expander_utils.c \
				./src/expanding/expander_utils2.c \
				./src/expanding_heredoc/heredoc_dollar.c \
				./src/expanding_heredoc/heredoc_expanding.c \
				./src/expanding_heredoc/heredoc_pid.c \
				./src/expanding_heredoc/heredoc_utils.c \
				./src/expanding_heredoc/heredoc_utils2.c \
				./src/expanding_heredoc/heredoc_exit.c \
				./src/expanding_heredoc/free_heredocs.c \
				./src/heredoc/check_heredocs.c \
				./src/heredoc/heredoc.c \
				./src/commands/build_commands.c \
				./src/commands/build_inits_and_nodes.c \
				./src/commands/build_redirections.c \
				./src/commands/build_utils.c \
				./src/commands/build_utils2.c \
				./src/execute/execute.c \
				./src/execute/parent_execute.c \
				./src/execute/pipes.c \
				./src/execute/find_path.c \
				./src/redirecting/redirect.c \
				./src/redirecting/child_redirect.c \
				./src/redirecting/parent_redirect.c \
				./src/signals/echoctl.c \
				./src/signals/ia_signals.c \
				./src/signals/nia_signals.c \
				./src/signals/hdoc_signals.c \
				./src/signals/hdoc_parent_signals.c \
				./src/builtins/builtins.c \
				./src/builtins/cd.c \
				./src/builtins/echo.c \
				./src/builtins/pwd.c \
				./src/builtins/export.c \
				./src/builtins/export_utils.c \
				./src/builtins/unset.c \
				./src/builtins/env.c \
				./src/builtins/exit.c \
				./src/utils/free_and_error.c\
				./src/utils/utils.c \
				./src/utils/syntax_check.c \
				./src/utils/testing.c


# Object files and directories
# obj folder in src?: src/obj 
OBJ 	= $(addprefix $(OBJDIR)/, $(notdir $(SRC:.c=.o)))
OBJDIR	= obj

# ANSI escape colors for messages


# Objectives
all: $(LIBFT) $(OBJDIR) $(NAME)
	@echo "Compilation Done"

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(LFLAGS) -o $(NAME)

$(LIBFT):
	@$(MAKE) -s -C ./libft

# Object files
$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: ./src/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/environment/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/nodes/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/tokenize/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/expanding/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/commands/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/heredoc/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/execute/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/parsing/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/redirecting/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/expanding_heredoc/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/signals/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/builtins/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/utils/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

# Cleaning
clean:
	@$(MAKE) -s clean -C ./libft
	@$(RM) $(OBJ)
	@echo "Cleaned object files"

fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -s fclean -C ./libft
	@rmdir  $(OBJDIR)
	@echo "Cleaned executor"

re: fclean all

.PHONY: all libft clean fclean re
