# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::   #
#    Makefile                                           :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: user <user@student.42.fr>                  +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2026/02/03 00:00:00 by user             #+#    #+#             #
#    Updated: 2026/02/03 00:00:00 by user            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	bounce

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -f

SRCS		=	main.c \
				init.c \
				ball.c \
				collision.c \
				collision2.c \
				game.c \
				game2.c \
				render.c \
				window.c \
				winproc.c \
				winproc2.c

OBJS		=	$(SRCS:.c=.o)

HEADER		=	boun.h

LIBS		=	-lgdi32 -lm

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

%.o:			%.c $(HEADER)
				$(CC) $(CFLAGS) -c $< -o $@

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re
