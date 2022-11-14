# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 14:04:53 by tbrandt           #+#    #+#              #
#    Updated: 2022/11/14 12:11:59 by tbrandt          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g #fsanitize=address
NAME	=	minishell

SRC		=	main.c						\
			lexer/echoctl.c				\
			lexer/add_space.c			\
			lexer/add_space2.c			\
			lexer/expend2.c				\
			lexer/get_word.c			\
			lexer/word_in_list.c		\
			lexer/join_and_free.c		\
			lexer/expend.c				\
			lexer/parsing2.c			\
			lexer/parsing.c				\
			lexer/utils.c				\
			parser/tokenize.c			\
			parser/redirection_out.c	\
			parser/heredoc.c			\
			parser/pipe_and_fork.c		\
			executor/exec.c				\
			executor/get_path.c			\
			executor/get_command.c		\
			executor/utils2.c			\
			built_in/export.c			\
			built_in/echo.c				\
			built_in/pwd.c				\
			built_in/pwd_utils.c		\
			built_in/utils.c			\
			built_in/utils2.c			\
			built_in/utils3.c			\
			built_in/utils4.c			\
			built_in/utils5.c			\
			built_in/utils6.c			\
			built_in/utils7.c			\
			built_in/utils8.c			\
			built_in/utils9.c			\
			built_in/utils10.c			\

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
