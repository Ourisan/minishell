SRCS		= ft_printf_utils.c ft_printf.c 
OBJS		= ${SRCS:.c=.o}
NAME		= libftprintf.a
CC			= cc
CFLAGS		= -Werror -Wall -Wextra

all:	$(NAME)

$(NAME): $(OBJS) ft_printf.h
	ar -rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
