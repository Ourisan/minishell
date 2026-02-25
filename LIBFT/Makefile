LIBFT_SRCS	= SRC/ft_atoi.c \
			  SRC/ft_atol.c \
			  SRC/ft_bzero.c \
			  SRC/ft_calloc.c \
			  SRC/ft_isalnum.c \
			  SRC/ft_isalpha.c \
			  SRC/ft_isascii.c \
			  SRC/ft_isdigit.c \
			  SRC/ft_isprint.c \
			  SRC/ft_itoa.c \
			  SRC/ft_memchr.c \
			  SRC/ft_memcmp.c \
			  SRC/ft_memcpy.c \
			  SRC/ft_memmove.c \
			  SRC/ft_memset.c \
			  SRC/ft_putchar_fd.c \
			  SRC/ft_putendl_fd.c \
			  SRC/ft_putnbr_fd.c \
			  SRC/ft_putstr_fd.c \
			  SRC/ft_split.c \
			  SRC/ft_strchr.c \
			  SRC/ft_strdup.c \
			  SRC/ft_strndup.c \
			  SRC/ft_striteri.c \
			  SRC/ft_strjoin.c \
			  SRC/ft_strlcat.c \
			  SRC/ft_strlcpy.c \
			  SRC/ft_strlen.c \
			  SRC/ft_strmapi.c \
			  SRC/ft_strncmp.c \
			  SRC/ft_strnstr.c \
			  SRC/ft_strrchr.c \
			  SRC/ft_strtrim.c \
			  SRC/ft_substr.c \
			  SRC/ft_tolower.c \
			  SRC/ft_toupper.c \
			  SRC/ft_lstadd_back_bonus.c \
			  SRC/ft_lstadd_front_bonus.c \
			  SRC/ft_lstclear_bonus.c \
			  SRC/ft_lstmap_bonus.c \
			  SRC/ft_lstdelone_bonus.c \
			  SRC/ft_lstiter_bonus.c \
			  SRC/ft_lstlast_bonus.c \
			  SRC/ft_lstnew_bonus.c \
			  SRC/ft_lstsize_bonus.c

GNL_SRCS 	= SRC/GNL/get_next_line.c \
			  SRC/GNL/get_next_line_utils.c

PRINTF_SRCS = SRC/printf/ft_printf.c \
			  SRC/printf/ft_printf_utils.c

SRCS = $(LIBFT_SRCS) $(GNL_SRCS) $(PRINTF_SRCS)
OBJS = $(SRCS:.c=.o)

NAME		= libft.a
CC			= cc
CFLAGS		= -Werror -Wall -Wextra

all:	$(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS) $(OBJS_BONUS)
	ar -rcs $(NAME) $(OBJS) $(OBJS_BONUS)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re bonus
