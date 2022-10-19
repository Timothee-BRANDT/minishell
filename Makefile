# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 14:04:53 by tbrandt           #+#    #+#              #
#    Updated: 2022/10/10 09:49:43 by mmatthie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g #-fsanitize=address
NAME	=	minishell

SRC		=	main.c					\
			parsing/add_space.c		\
			parsing/get_word.c		\
			parsing/word_in_list.c	\
			parsing/join_and_free.c		\
			parsing/expend.c		\
			parsing/parsing2.c		\
			parsing/parsing.c		\
			built_in/export.c		\
			built_in/utils.c		\
			built_in/utils2.c		\
			built_in/utils3.c		\

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
