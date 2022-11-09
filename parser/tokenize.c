/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:42:43 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/04 15:03:28y tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_tokenisation(t_list *list)
{
	t_list *tmp;

	tmp = list;
	while (tmp && tmp->next)
	{
		if (ft_strcmp((char *)list->content, "<") == 0)
			list->token = REDIR_IN;
		if (ft_strcmp((char *)list->content, ">") == 0)
			list->token = REDIR_OUT;
		if (ft_strcmp((char *)list->content, "<<") == 0)
			list->token = DELIM;
		if (ft_strcmp((char *)list->content, ">>") == 0)
			list->token = APPEND;
		if (ft_strcmp((char *)list->content, "|") == 0)
			list->token = PIPE;
		list = list->next;
		tmp = list;
	}
}

int	token_error(t_list *list)
{
	t_list *tmp;

	if (!list)
		return (0);
	tmp = list;
	if (is_token((char *)tmp->content) && !tmp->next)
		return (1);
	while (tmp && tmp->next)
	{
		if (is_token((char *)tmp->next->content) && !tmp->next->next)
			return (1);
		if (is_token((char *)tmp->content) && is_token((char *)tmp->next->content))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	built_in_tokenisation(t_list *list)
{
	t_list *tmp;

	tmp = list;
	while (tmp && tmp->next)
	{
		if (!ft_strcmp((char *)list->content, "echo") || !ft_strcmp((char *)list->content, "ECHO"))
			list->token = ECHO;
		if (!ft_strcmp((char *)list->content, "cd") || !ft_strcmp((char *)list->content, "CD"))
			list->token = CD;
		if (!ft_strcmp((char *)list->content, "pwd") || !ft_strcmp((char *)list->content, "PWD"))
			list->token = PWD;
		if (!ft_strcmp((char *)list->content, "export") || !ft_strcmp((char *)list->content, "EXPORT"))
			list->token = EXPORT;
		if (!ft_strcmp((char *)list->content, "unset") || !ft_strcmp((char *)list->content, "UNSET"))
			list->token = UNSET;
		if (!ft_strcmp((char *)list->content, "env") || !ft_strcmp((char *)list->content, "ENV"))
			list->token = ENV;
		if (!ft_strcmp((char *)list->content, "exit") || !ft_strcmp((char *)list->content, "EXIT"))
			list->token = EXIT;
		list = list->next;
		tmp = list;
	}
}

void	exec_builtin(char **tab, t_data *data)
{
	if (!tab)
		return ;
	if (is_export(tab, data))
		return ;
	if (is_unset(tab, data))
		return ;
	if (is_cd(tab, data))
		return;
}

int	get_len(char **tab)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (!tab)
		return (0);
	while(tab[i] && ft_strcmp(tab[i], "|"))
	{
		i++;
		result++;
	}
	return (result);
}

char	**get_next_pipe(char **tab)
{
	char 	**result;
	int		i;
	int		len;

	i = 0;
	len = get_len(tab);
	result = malloc(sizeof(char *) * (len + 1));
	while (tab[i] && ft_strcmp(tab[i], "|"))
	{
		result[i] = ft_strdup(tab[i]);
		i++;
	}
	result[i] = NULL;
	return (result);
}

void	start_builtin(t_data *data)
{
	char **command;
	char **tab;

	tab = get_cmd_from_list_v2(data->list, data);
	check_if_pipe(tab, data);
	command = get_next_pipe(tab);
	free_tab(tab);
	exec_builtin(command, data);
	free_tab(command);
}

int	analyzer(t_data *data, t_cmd *cmd)
{
	data->tmp_in = dup(0);
	data->tmp_out = dup(1);
	
	if (token_error(data->list))
	{
		close(data->tmp_in);
		close(data->tmp_out);
		return (on_error("Minishell: syntax error near unexpected token\n", 1));
	}
	redir_tokenisation(data->list);
	built_in_tokenisation(data->list);
	get_cmd_size(data->list, data);
	get_cmd_count(data->list, data);
	if (check_all_infile(data->list, data))
		return (on_error("Infile not found\n", 1));
	if (count_heredoc(data->list))
		start_heredoc(data);
	start_builtin(data);
	start_exec(cmd, data);
	return (0);
}