#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_data{
        char *buffer;
        char *tmp;
		t_list	*env;
        t_list  *export;
}       t_data;

int	    check_space(char *buffer);
void	ft_print_list(t_list	*lst);
void	ft_print_env(t_list	*lst);
int     on_error(char *str, int code);
int		check_quote(t_data *data);
t_list  *create_list(t_data *data);
t_list	*env_to_list(char **env);
int     export_name(t_list **env, t_list **export, char *name);
int     is_in_list(t_list **list, char *name);
void    unset_name_env(t_list **env, char *name);
void    unset_name_export(t_list **export, char *name);

#endif
