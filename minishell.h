/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:34:14 by mmatthie          #+#    #+#             */
/*   Updated: 2022/10/02 16:51:30 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>

enum e_redir {
	WORD,
	REDIR_IN,
	REDIR_OUT,
	DELIM,
	APPEND,
	PIPE,
};

enum e_built_in {
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
};

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
	int		append;
	int		check;
	int		cmd_count;
	int		pipe_count;
	int		cmd_size;
	int		plus;
	int		tmp_in;
	int		tmp_out;
	int		restore_redir;
	char	*infile;
	char	*outfile;
	char	*delimitor;
	char	*str;
	char	*string;
	char	*get_key;
	char	*result;
	char	*get_key_export;
	char	*get_key_name;
	char	*get_value_export;
	char	*get_value_name;
	t_list	*env;
	t_list	*export;
	t_list	*tmp;
	t_list	*list;
}				t_data;

typedef struct s_cmd
{
	char	**args;
	t_list	*redirs;
}	t_cmd;

//utils.c
t_list	*get_in_list(char	*buffer, t_data	*data, t_list	*lst);
int		on_error(char *str, int code);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
void	ft_print_list(t_list	*lst);
int		check_quote(char *buffer);
int		ft_isspace(int c);
int		get_quotes(char	*buffer, t_data	*data, int count);
void	ft_manage(void	*to_add);
void	ft_free_list(t_list	**lst);
int		is_built_in(void *content);
void	free_tab(char **tab);
int		is_token(char *str);
int		is_redir(char *str);
int		is_pipe(char*str);

//check.c 
t_list	*ft_list(t_list	*lst, t_data *data);
t_list	*get_word_in_list(char	*buffer, t_data	*data);
int		get_second_word(char	*buffer, int count, t_data	*data);
char	*ft_join_free_ss(char *s1, char *s2);
int		get_word(char	*buffer, t_data	*data, int count);
int		get_join(char	*str, int count, int j, t_data	*data);
int		get_without_quotes(char	*buffer, t_data	*data, int count);
int		make_second(char	*buffer, t_data	*data, int count);

//parser
void	built_in_analyzer(t_list **list, t_data	*data);
int		analyzer(t_data *data, t_cmd *cmd);
void	redir_tokenisation(t_list *list);
int		get_redir_file(t_list **list, t_data *data);
void	remove_pipe(t_list **list);
void	remove_redir(t_list **list);
void	get_cmd_count(t_list *list, t_data *data);
void	get_cmd_size(t_list *list, t_data *data);
void	free_command(t_list **list, t_data *data);
void    get_cmd_from_list(t_list**list, t_data *data, t_cmd *cmd);

// redirections
void	restore_redir(t_data *data);
int		check_in_redirections(t_list *list, t_data *data);
int		redirect_in(t_data *data);

// executor
char	*get_correct_cmd(char **paths, char **cmds);
void    exec_command(t_cmd *cmd, t_data *data);
char	**get_all_path(t_data *data);


//export.c
t_list	*env_to_list(char **env);
int		is_in_list(t_list **list, char *name);
void	found_and_replace(t_list **export, char *name);
void	found_and_add(t_list **export, char *name, t_data *data);
void	exec_export(t_data *data);
int		export_name(t_list **list, t_data *data, int code);
void	unset_name_env(t_list **env, t_list **cmd);
void	unset_name_export(t_list **export, t_list **list);
char	*ft_strjoin_export(char const *s1, char const *s2);
void	init_data(t_data *data);
int		set_export_var(t_data *data);
char	*ft_get_value(char *str);
char	*remove_plus(char *str);
char	*ft_get_key(char *str);
void	ft_print_env(t_list	*lst);
void	free_all(t_data *data);
void	free_two_string(char *s1, char *s2);
char    **list_to_tab(t_list *list);
void	free_three_string(char *s1, char *s2, char *s3, char *s4);

#endif
