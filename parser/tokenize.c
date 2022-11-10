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

int	exec_builtin(char **tab, t_data *data)
{
	if (!tab)
		return (1);
	if (!is_export(tab, data))
		return (1);
	else if (!is_env(tab, data))
		return (1);
	else if (!is_unset(tab, data))
		return (1);
	else if (!is_cd(tab, data))
		return (1);
	else if (!is_pwd(tab, data))
		return (1);
	else if (!is_echo(tab, data))
		return (1);
	return (0);
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

int	start_builtin(t_data *data)
{
	char **command;
	char **tab;

	tab = get_cmd_from_list_v2(data->list, data);
	check_if_pipe(tab, data);
	command = get_next_pipe(tab);
	free_tab(tab);
	if (exec_builtin(command, data))
	{
		free_tab(command);
		return (1);
	}
	free_tab(command);
	return (0);
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
	get_cmd_size(data->list, data);
	get_cmd_count(data->list, data);
	if (check_all_infile(data->list, data))
	{
		close(data->tmp_in);
		close(data->tmp_out);
		return (on_error("Infile not found\n", 1));
	}
	if (count_heredoc(data->list))
		start_heredoc(data);
	if (start_builtin(data))
	{
		close(data->tmp_in);
		close(data->tmp_out);
		return (0);
	}
	start_exec(cmd, data);
	return (0);
}