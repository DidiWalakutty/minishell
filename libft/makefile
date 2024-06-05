NAME 	= libft.a
GFLAGS = -Wall -Werror -Wextra

CC = cc

L_OBJDIR = obj/
SRCS = ft_bzero.c ft_calloc.c ft_isascii.c ft_split.c ft_strdup.c \
		ft_strlen.c ft_substr.c iswhitespace.c ft_strchr.c ft_strtrim.c \
		ft_strnstr.c \
		ft_printf.c print_char.c print_str.c print_nbr.c print_pointer.c \
		print_uns_dec.c print_lowerhex.c print_upperhex.c \

OBJ = $(SRCS:%.c=$(L_OBJDIR)%.o)

CFLAGS = -Wall -Werror -Wextra

RM = rm -f

all: $(L_OBJDIR) $(NAME)

$(L_OBJDIR):
	@mkdir -p $(L_OBJDIR)

AR = ar -rcs

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)

$(L_OBJDIR)%.o:%.c
	@$(CC) $(GFLAGS) -c -o $@ $<

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)
	@rmdir $(L_OBJDIR)

re: fclean all

.PHONY: all clean fclean re
