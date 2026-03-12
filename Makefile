# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-plac <lde-plac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/23 17:29:24 by lde-plac          #+#    #+#              #
#    Updated: 2026/03/12 23:08:53 by lde-plac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -g3

SRCS		=	SRC/main.c \
				SRC/utils.c \
				SRC/executor.c \
				SRC/redir.c \
				SRC/lexer.c \
				SRC/token.c \
				SRC/parsing.c \
				SRC/parsing_list.c \
				SRC/parsing_check.c \
				SRC/builtins.c \
				SRC/builtins_env.c \
				SRC/builtins_utils.c \
				SRC/env.c

OBJS		=	$(SRCS:.c=.o)

LIBFT_DIR	=	LIBFT
LIBFT		=	$(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
