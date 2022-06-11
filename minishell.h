#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

int	    check_space(char *buffer);
t_list  *create_list(char **buffer_splited);
void	ft_print_list(t_list	*lst);

#endif
