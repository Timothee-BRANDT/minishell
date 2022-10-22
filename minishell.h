/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:34:14 by mmatthie          #+#    #+#             */
/*   Updated: 2022/10/22 13:14:10 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
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
	// parsing manu
	char	*first;
	char	*second;
	char	*join;
	char	*buffer;
	char	*get_word;
	char	*str;
	char	*string;
	int		step;
	int		count;
	int		indicate;
	int		plus;
	int		token;
	int		i;
	int		statique;
	int		append;
	int		check;
	// redirections
	int		cmd_count;
	int		pipe_count;
	int		cmd_size;
	int		fd_in;
	int		fd_out;
	int		fdd;
	int		tmp_in;
	int		tmp_out;
	int		pipe_0;
	int		pipe_1;
	int		last_redir;
	int		last_cmd;
	int		check_fd;
	int		check_fd_in;
	int		check_fd_out;
	int		reset_prompt;
	char	*first_outfile;
	char	*infile;
	char	*outfile;
	char	*delimitor;
	// built-ins
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
void	ft_print_list(t_list	*lst);
void	ft_manage(void	*to_add);
void	ft_free_list(t_list	*lst);
void	free_tab(char **tab);
void	print_tab(char **tab);
void	free_2_tab(char **tab1, char **tab2);
char	**lst_to_tab(t_list *list, t_data *data);
int		on_error(char *str, int code);
int		open_error(char *infile, char *outfile);
int		check_quote(char *buffer);
int		ft_isspace(int c);
int		get_quotes(char	*buffer, t_data	*data, int count);
int		is_built_in(void *content);
int		is_token(char *str);
int		is_redir(char *str);
int		is_pipe(char*str);
char	*ft_strncpy(char *dest, char *src, unsigned int n);

//check.c 
int		get_second_word(char	*buffer, int count, t_data	*data);
int		get_word(char	*buffer, t_data	*data, int count);
int		get_join(char	*str, int count, int j, t_data	*data);
int		get_without_quotes(char	*buffer, t_data	*data, int count);
int		make_second(char	*buffer, t_data	*data, int count);
char	*ft_join_free_ss(char *s1, char *s2);
char	*get_env(char *key, t_list *env);
t_list	*ft_list(t_list	*lst, t_data *data);
t_list	*get_word_in_list(char	*buffer, t_data	*data);

//parser
void	built_in_analyzer(t_list **list, t_data	*data);
void	remove_pipe(t_list *list, t_data *data);
void	redir_tokenisation(t_list *list);
void	get_cmd_count(t_list *list, t_data *data);
void	get_cmd_size(t_list *list, t_data *data);
void	free_command(t_list *list, t_data *data);
void    get_cmd_from_list(t_list *list, t_data *data, t_cmd *cmd);
void	free_list(void *ptr);
int		analyzer(t_data *data, t_cmd *cmd);
int		token_error(t_list *list);
int		get_first_redir_out(t_list *list, t_data *data);
int		get_first_redir_in(t_list *list, t_data *data);
int		check_all_infile(t_list *list, t_data *data);
void	get_fd_and_free(t_list *list, t_data *data);
char	**extract_cmd(char **cmd, t_data *data);
t_list	*remove_args(t_list *list, t_data *data);

// redirections
void	remove_in_redir(t_list *list);
int		skip_hd(char **cmd, int *k);
void	remove_out_redir(t_list *list);
int		get_first_redirection_before_pipe(t_data *data);
int		check_in_redirection(t_list *list, t_data *data);
int		check_out_redirection_before_pipe(t_list *list, t_data *data);
int		redirect_in(t_data *data);
int		redirect_out(t_data *data);
int		get_redir_count(t_list *list);
int		start_heredoc(t_data *data);
int		count_heredoc(t_list *list);
char	**stock_delimitors(t_list *list, t_data *data);
void	redir_out_manager(int *j, char **cmd, t_data *data);
int		redir_in_manager(int *k, char **cmd, t_data *data);
int		check_if_another_redir_in(int	*k, char **cmd, t_data *data);

// executor
void    exec_command(char **cmds, t_data *data);
void	forking(t_cmd *cmd, t_data *data, int pipe_fd0, int pipe_fd1);
void    restore_fd(t_data *data);
void    dup_child_exec(char **cmd, t_data *data, int cmd_count);
void	dup_parent(t_data *data, int cmd_count);
void	create_pipe(t_data *data);
void	redir_fd_out(t_data *data);
int		start_exec(t_cmd *cmd, t_data *data);
int		wait_my_childs(t_data *data);
char	*get_correct_cmd(char **paths, char **cmds);
char	**get_all_path(t_data *data);
char 	**get_last_cmd(char **tab);


//export.c
t_list	*env_to_list(char **env);
void	found_and_replace(t_list **export, char *name);
void	found_and_add(t_list **export, char *name, t_data *data);
void	exec_export(t_data *data);
void	unset_name_env(t_list **env, t_list **cmd);
void	unset_name_export(t_list **export, t_list **list);
void	init_data(t_data *data);
void	ft_print_env(t_list	*lst);
void	free_all(t_data *data);
void	free_two_string(char *s1, char *s2);
void	free_three_string(char *s1, char *s2, char *s3, char *s4);
int		export_name(t_list **list, t_data *data, int code);
int		is_in_list(t_list **list, char *name);
int		set_export_var(t_data *data);
char	*ft_strjoin_export(char const *s1, char const *s2);
char	*ft_get_value(char *str);
char	*remove_plus(char *str);
char	*ft_get_key(char *str);
char    **list_to_tab(t_list *list);

#endif
