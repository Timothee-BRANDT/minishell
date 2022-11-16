/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 19:34:14 by mmatthie          #+#    #+#             */
/*   Updated: 2022/11/16 14:26:03 by tbrandt          ###   ########.fr       */
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
# include <signal.h>
# include <errno.h>
# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <termios.h>

typedef struct s_glo
{
	int	g_signum;
	int	g_prompt;
	int	ctrl;
}	t_glo;

t_glo	g_glo;

typedef struct s_data
{
	int		i_space;
	int		j_space;
	char	*first;
	char	*second;
	int		i_get;
	int		j_get;
	char	*join;
	char	*buffer;
	char	*get_word;
	char	*buffer_save;
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
	char	*expend;
	char	*dollarplusquotes;
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
	int		append;
	int		check_fd_out;
	int		check_pipe;
	int		reset_prompt;
	int		*fd;
	char	*first_outfile;
	char	*infile;
	char	*outfile;
	char	*delimitor;
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
	char	**tab;
}	t_cmd;

//utils.c
t_list	*get_in_list(char	*buffer, t_data	*data, t_list	*lst);
void	ft_print_list(t_list	*lst);
void	ft_manage(void	*to_add);
void	ft_free_split(char **tab);
void	free_tab(char **tab);
void	print_tab(char **tab, t_data *data);
void	free_2_tab(char **tab1, char **tab2, t_data *data);
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
void	ctrl_c(int sig);
int		set_sig(int sig);
void	tty_hide_ctrl(void);
void	tty_show_ctrl(void);
void	unset_tty(t_data	*data, char	**env);
void	stop_handler(int sig);

//lexer
void	little_one(t_data	*data);
int		get_expend_without_first(char	*str, int count, t_data	*data);
void	do_else(t_data	*data);
char	*ft_join_free_s1(char *s1, char *s2);
int		make_expend(char	*str, int j, int content, t_data	*data);
int		last_token(int count, t_data	*data);
int		ft_check_token(char c);
int		fill_quotes(char *dest, char	*buffer, t_data	*data);
void	expend_it(t_data	*data, char	*str, int j);
char	*ft_itoa_v2(int n);
int		exit_code(int signum);
void	set_redir(t_data	*data, char	*str, char	*buffer);
void	set_redir(t_data	*data, char	*str, char	*buffer);
int		reset_indicate(int count, t_data	*data);
void	free_2_string(char *s1, char *s2);
int		get_next(char	*str, int i, t_data	*data, int tmp);
int		get_token(t_data	*data, char	*buffer, int count);
int		first_expend(char	*str, int count, t_data	*data);
void	print_it(char	*ptr);
char	*ft_join_free_ss(char *s1, char *s2);
int		get_expend(char	*str, int j, int count, t_data	*data);
void	check_token(char	*buffer, int count, t_data	*data);
int		get_second_simple(char	*str, int count, t_data	*data);
int		get_second_double(char	*str, int count, t_data	*data);
int		get_second_with_token(char	*str, int count, t_data	*data);
int		get_second_without_token(char	*str, int count, t_data	*data);
int		get_expend_with_token(char	*str, int j, int count, t_data	*data);
char	*get_env(char *key, t_list *env);
char	*ft_add_space(char	*buffer, t_data	*data);
void	free_it(char	*str);
void	set_data(t_data	*data);
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
int		make_second(char	*buffer, t_data	*data, int count);
t_list	*ft_list(t_list	*lst, t_data *data);
t_list	*get_word_in_list(char	*buffer, t_data	*data);
int		get_join_and_free(char	*str, int count, t_data	*data);
int		get_second_word(char	*buffer, int count, t_data	*data);
int		get_word(char	*buffer, t_data	*data, int count);
int		get_join(char	*str, int j, t_data	*data);
int		get_without_quotes(char	*buffer, t_data	*data, int count);
void	get_and_free(t_data *data);

//parser
void	built_in_analyzer(t_list **list, t_data	*data);
void	redir_tokenisation(t_list *list);
void	get_cmd_count(t_list *list, t_data *data);
void	get_cmd_size(t_list *list, t_data *data);
void	get_cmd_from_list(t_list *list, t_data *data, t_cmd *cmd);
char	**get_cmd_from_list_v2(t_list *list, t_data *data);
void	free_list(void *ptr);
int		analyzer(t_data *data, t_cmd *cmd);
int		token_error(t_list *list);
int		check_all_infile(t_list *list, t_data *data);
char	**extract_cmd(char **cmd, t_data *data);

// redirections
int		start_heredoc(t_data *data);
int		count_heredoc(t_list *list);
char	**stock_delimitors(t_list *list, t_data *data);
void	redir_out_manager(int *j, char **cmd, t_data *data);
int		redir_in_manager(int *k, char **cmd, t_data *data);

// executor
void	exec_command(char **cmds, t_data *data);
void	restore_fd(t_data *data);
void	dup_child_exec(char **cmd, t_data *data, int cmd_count);
void	dup_parent(t_data *data, int cmd_count);
void	create_pipe(t_data *data);
void	redir_fd_out(t_data *data);
void	start_exec(t_cmd *cmd, t_data *data);
int		wait_my_childs(t_data *data);
char	*get_correct_cmd(char **paths, char **cmds);
char	**get_all_path(t_data *data);
char	**get_last_cmd(char **tab);
int		final_cmd_size(char **cmd);
void	check_all_redirection(char **cmd, int *k, t_data *data);

//builtins
void	found_and_replace(t_list **export, char *name);
void	found_and_add(t_list **export, char *name, t_data *data);
void	exec_export(t_data *data);
void	unset_name_env(t_list **env, t_list **cmd);
void	unset_name_export(t_list **export, t_list **list);
void	init_data(t_data *data);
void	ft_print_env(t_list *lst);
void	free_all(t_data *data);
void	free_two_string(char *s1, char *s2);
void	free_three_string(char *s1, char *s2, char *s3, char *s4);
int		export_name(t_list **list, t_data *data);
int		is_in_list(t_list **list, char *name);
char	*get_env_v2_export(char *key, t_data *data);
char	*get_env_v2_env(char *key, t_data *data);
int		set_export_var(t_data *data);
char	*ft_strjoin_export(char const *s1, char const *s2);
char	*ft_get_value(char *str);
char	*remove_plus(char *str);
char	*ft_get_key(char *str);
char	**list_to_tab(t_list *list);
int		check_builtin(char *str, t_data *data);
int		redirect_in_builtin(char **cmds, t_data *data);
void	start_echo(char **cmds);
char	**get_next_pipe(char **tab);
int		get_len(char **tab);
void	skip_builtin(char **cmd, int *k, t_data *data);
void	print_echo(char **cmds, char *result);
int		check_option(char *tab);
int		is_export_main(char **tab, t_data *data);
int		is_unset_main(char **tab, t_data *data);
int		is_pwd_main(char **tab, t_data *data);
int		is_cd_main(char **tab, t_data *data);
int		is_env_main(char **tab, t_data *data);
int		is_echo_main(char **tab, t_data *data);
int		is_export_child(char **tab, t_data *data);
int		is_unset_child(char **tab, t_data *data);
int		is_pwd_child(char **tab, t_data *data);
int		is_cd_child(char **tab, t_data *data);
int		is_env_child(char **tab, t_data *data);
int		is_exit(char **tab);
int		is_echo_child(char **tab, t_data *data);
int		check_if_pipe(char **tab, t_data *data);
int		start_builtin(t_data *data, char **args, char **cmds);
int		check_if_pipe(char **tab, t_data *data);
int		chdir_home(t_data *data);
int		str_error(char *str);
void	change_oldpwd_env(t_data *data, char *pwd);
void	change_oldpwd_export(t_data *data, char *pwd);
void	change_pwd_env(t_data *data);
void	change_pwd(t_data *data, char *pwd);
void	set_glo(void);
void	hd_norm(void);
void	hd_norm_2(char *str, int fd);
void	change_pwd_export(t_data *data);
int		error_open(char **tab, char *pwd);
t_list	*env_to_list(char **env);
t_list	*dpt_to_lst_export(char **env);
t_list	*dpt_to_lst_env(char **env);

#endif