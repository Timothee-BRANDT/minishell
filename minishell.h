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
        char    *buffer;
        char    *tmp;
		t_list	*env;
        t_list  *export;
        char	*first;
    	char	*second;
    	char	*join;
    	char	*get_word;
    	int		step;
    	int		count;
        int		indicate;
}       t_data;

int	    check_space(char *buffer);
char	*remove_plus(char *str);
void	ft_print_list(t_list	*lst);
void	ft_print_env(t_list	*lst);
int     on_error(char *str, int code);
int		check_quote(t_data *data);
char 	*ft_get_key(char *str);
char	*ft_get_value(char *str);
int		is_token(char *str);
t_list  *create_list(t_data *data);
t_list	*env_to_list(char **env);
int     export_name(t_list **env, t_list **export, t_list **cmd, int code);
int     is_in_list(t_list **list, char *name);
void    unset_name_env(t_list **env, char *name);
void    unset_name_export(t_list **export, char *name);
int		get_word(char	*buffer, t_data	*data);
t_list	*get_word_in_list(char	*buffer, t_data	*data);
char	*ft_strjoin_export(char const *s1, char const *s2);
t_list	*ft_list(t_list	*lst, char	*str);
int     ft_isspace(int c);
int     get_word(char	*str, t_data *data);
char	*ft_strncpy(char *dest, char *src, unsigned int n);

#endif
