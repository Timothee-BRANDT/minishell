/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:34:14 by mmatthie          #+#    #+#             */
/*   Updated: 2022/06/21 15:11:54 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_data
{
	char	*first;
	char	*second;
	char	*join;
	char	*buffer;
	char	*get_word;
	int		step;
	int		count;
	int		indicate;
	int		token;
	int		i;
	int		check;
	int		plus;
	char	*str;
	char	*get_key;
	t_list	*env;
	t_list	*export;
	t_list	*cmd;
}				t_data;

//utils.c
char	*ft_strncpy(char *dest, char *src, unsigned int n);
void	ft_print_list(t_list	*lst);
int		check_quote(char *buffer);
int		ft_isspace(int c);
int		get_quotes(char	*buffer, t_data	*data, int count);

//main.c
t_list	*ft_list(t_list	*lst, char	*str);
t_list	*get_word_in_list(char	*buffer, t_data	*data);
int		make_second(char	*buffer, t_data	*data, int count);

//check.c 
int		get_second_word(char	*buffer, int count, t_data	*data);
char	*ft_join_free_ss(char *s1, char *s2);
int		get_word(char	*buffer, t_data	*data, int count);
int		get_join(char	*str, int count, int j, t_data	*data);
int		get_without_quotes(char	*buffer, t_data	*data, int count);

//export.c
t_list	*env_to_list(char **env);
int		is_in_list(t_list **list, char *name);
void	found_and_replace(t_list **export, char *name);
void	found_and_add(t_list **export, char *name);
void	exec_export(t_data *data);
int		export_name(t_list **cmd, t_data *data, int code);
void	unset_name_env(t_list **env, t_list **cmd);
void	unset_name_export(t_list **export, t_list **cmd);
void	ft_export(t_list **cmd, t_data	*data);
char	*ft_strjoin_export(char const *s1, char const *s2);
int		is_token(char *str);
char	*ft_get_value(char *str);
char	*remove_plus(char *str);
char	*ft_get_key(char *str);
void	ft_print_env(t_list	*lst);

#endif
