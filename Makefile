NAME	=	minishell

# Libraries and Headers
LIBFT	= ./libft/libft.a
HEADERS	= -I includes -I $(LIBFT)/headers

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
				./src/environment/env.c \
				./src/nodes/nodes.c \
				./src/utils/free_and_error.c\
				./src/tokenize/lexer.c \
				./src/tokenize/quotes.c \
				./src/tokenize/tokenize_utils.c \
				./src/tokenize/tokenizer.c \
				./src/execute/pipes.c \
				./src/builtins/echo.c \
				./src/builtins/cd.c \
				./src/builtins/pwd.c
				# ./src/expanding/expander.c \
				# ./src/expanding/expander_utils.c \
				# ./src/expanding/expander_checks.c \
				# ./src/expanding/expander_handler.c \

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

$(OBJDIR)/%.o: ./src/utils/%.c
		@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/execute/%.c
		@$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $<

$(OBJDIR)/%.o: ./src/builtins/%.c
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
