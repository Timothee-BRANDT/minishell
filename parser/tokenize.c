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
	t_list *command;

	if (!ft_strcmp(tab[0], "export"))
	{
		if (!tab[1])
        	ft_print_env(data->export);
		else if (ft_strlen2d(tab) > 1)
		{
			command = dpt_to_lst(tab);
			export_name(&command, data);
		}
	}
}

int	get_len(char **tab)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
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
	command = get_next_pipe(tab);
	ft_manage(tab);
	exec_builtin(command, data);
	ft_manage(command);
	// fonction qui remove tout jusqu'a la pipe si j'ai trouver une builtin
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