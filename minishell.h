/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:34:14 by mmatthie          #+#    #+#             */
/*   Updated: 2022/10/18 10:42:32 by mmatthie         ###   ########.fr       */
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
	int		i_space;
	int		j_space;
	char	*first;
	char	*second;
	char	*join;
	char	*buffer;
	char	*get_word;
	int		count;
	int		token;
	int		i;
	int		check;
	int		plus;
	int		res_space;
	int		index_space;
	int		space_len;
	int		indicate_expend;
	int		indicate;
	char	*str;
	char	*string;
	char	*get_key;
	char	*expend;
	char	*dollarplusquotes;
	char	*result;
	char	*get_key_export;
	char	*get_key_name;
	char	*get_value_export;
	char	*get_value_name;
	t_list	*env;
	t_list	*export;
	t_list	*tmp;
	t_list	*cmd;
}				t_data;

int		first_expend(char	*str, int count, t_data	*data);
void	print_it(char	*ptr);
void	check_token(char	*buffer, int count, t_data	*data);
int		get_second_simple(char	*str, int count, t_data	*data);
int		get_second_double(char	*str, int count, t_data	*data);
int		get_second_with_token(char	*str, int count, t_data	*data);
int		get_second_without_token(char	*str, int count, t_data	*data);
int		get_expend_with_token(char	*str, int j, int count, t_data	*data);
char	*get_env(char *key, t_list *env);

//add_space.c
char	*ft_add_space(char	*buffer, t_data	*data);

//parsing.c
void	free_it(char	*str);

//parsing2.c
void	set_data(t_data	*data);

//utils.c
t_list	*get_in_list(char	*buffer, t_data	*data, t_list	*lst);
int		on_error(char *str, int code);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
void	ft_print_list(t_list	*lst);
int		check_quote(char *buffer);
int		ft_isspace(int c);
int		get_quotes(char	*buffer, t_data	*data, int count);
int		get_double_quotes(char	*buffer, t_data	*data, int count);
int		get_simple_quotes(char	*buffer, int count, t_data *data);
void	ft_manage(void	*to_add);
void	ft_free_list(t_list	**lst);

//main.c
int		make_second(char	*buffer, t_data	*data, int count);

//check.c
t_list	*ft_list(t_list	*lst, t_data *data);
t_list	*get_word_in_list(char	*buffer, t_data	*data);
int		get_second_word(char	*buffer, int count, t_data	*data);
int		get_word(char	*buffer, t_data	*data, int count);
int		get_join(char	*str, int j, t_data	*data);
int		get_without_quotes(char	*buffer, t_data	*data, int count);

//export.c
t_list	*env_to_list(char **env);
int		is_in_list(t_list **list, char *name);
void	found_and_replace(t_list **export, char *name);
void	found_and_add(t_list **export, char *name, t_data *data);
void	exec_export(t_data *data);
int		export_name(t_list **cmd, t_data *data, int code);
void	unset_name_env(t_list **env, t_list **cmd);
void	unset_name_export(t_list **export, t_list **cmd);
void	ft_export(t_list **cmd, t_data	*data);
char	*ft_strjoin_export(char const *s1, char const *s2);
int		is_token(char *str);
void	init_data(t_data *data);
int		set_export_var(t_data *data);
char	*ft_get_value(char *str);
char	*remove_plus(char *str);
char	*ft_get_key(char *str);
void	ft_print_env(t_list	*lst);
void	free_all(t_data *data);
void	free_two_string(char *s1, char *s2);
void	free_three_string(char *s1, char *s2, char *s3, char *s4);

//expend.c
int		make_expend(char	*str, int j, int content, t_data	*data);
int		get_expend(char	*str, int j, int count, t_data	*data);
void	expend_it(t_data	*data, char	*str, int j);
int		fill_quotes(char *dest, char	*buffer, t_data	*data);

//join_and_free
char	*ft_join_free_s2(char *s1, char *s2);
char	*ft_join_free_s1(char *s1, char *s2);
char	*ft_join_free_ss(char *s1, char *s2);

#endif
