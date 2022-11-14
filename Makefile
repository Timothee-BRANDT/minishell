# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/09 14:04:53 by tbrandt           #+#    #+#              #
#    Updated: 2022/11/13 15:52:04 by mmatthie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g # -fsanitize=address

SRC		=	main.c						\
			signal/echoctl.c			\
			signal/signal.c				\
			signal/exit_code.c			\
			lexer/add_space.c			\
			lexer/add_space2.c			\
			lexer/ft_exit.c				\
			lexer/expend2.c				\
			lexer/get_word.c			\
			lexer/word_in_list.c		\
			lexer/join_and_free.c		\
			lexer/expend.c				\
			lexer/parsing2.c			\
			lexer/parsing.c				\
			lexer/utils.c				\
			lexer/utils2.c				\
			lexer/utils3.c				\
			parser/tokenize.c			\
			parser/redirection_out.c	\
			parser/heredoc.c			\
			parser/pipe_and_fork.c		\
			executor/exec.c				\
			executor/get_path.c			\
			executor/get_command.c		\
			executor/utils2.c			\
			built_in/export.c			\
			built_in/utils.c			\
			built_in/utils2.c			\
			built_in/utils3.c			\
			built_in/utils4.c			\
			built_in/utils5.c			\

OBJ		=	$(SRC:%.c=%.o)

# IF NEEDED @42 on MacOS10 Install :
#rm -rf $HOME/.brew && git clone --depth=1 https://github.com/Homebrew/brew $HOME/.brew && echo 'export PATH=$HOME/.brew/bin:$PATH' >> $HOME/.zshrc && source $HOME/.zshrc && brew update

LIBS	=	-L/Users/mmatthie/.brew/opt/readline/lib -Llibft -lft
HEADERS	=	-I/Users/mmatthie/.brew/opt/readline/include

all: $(NAME)

$(NAME): libft/libft.a $(OBJ)
	$(CC) ${CFLAGS} -o $(NAME) $(OBJ) ${LIBS} -I include -L libft -lft -lreadline -L./includes/readline/lib -lncurses

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

.PHONY: all run clean fclean remake
