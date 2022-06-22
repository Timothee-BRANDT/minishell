# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 14:04:53 by tbrandt           #+#    #+#              #
#    Updated: 2022/06/22 15:14:02 by tbrandt          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g #-fsanitize=address
NAME	=	minishell

SRC		=	main.c				\
			parsing/utils.c		\
			parsing/utils2.c	\
			parsing/check.c		\
			parsing/check2.c	\
			built_in/export.c	\
			built_in/utils.c	\
			built_in/utils2.c	\
			built_in/utils3.c	\

OBJ		=	$(SRC:%.c=%.o)

LIBS    =   -L/Users/tbrandt/.brew/opt/readline/lib -lreadline
HEADERS =   -I/Users/tbrandt/.brew/opt/readline/include

all: $(NAME)

$(NAME): libft/libft.a $(OBJ)
	$(CC) ${CFLAGS} -o $(NAME) $(OBJ) ${LIBS} -I include -L libft -lft

libft/libft.a:
	make -j -C libft

%.o: %.c
	$(CC) ${CFLAGS} -o $@ -c $< ${HEADERS}

clean:
	make clean -C libft
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all run clean fclean re make_libft
