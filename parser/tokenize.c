/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:42:43 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/01 18:16:52 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_tokenisation(t_list *list)
{
	t_list *tmp;

	tmp = list;
	while (tmp->next)
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

int	get_redir_file(t_list **list, t_data *data)
{
	t_list *tmp;

	tmp = *list;
	while (tmp->next)
	{
		if (is_token((char *)tmp->next->content) && !tmp->next->next)
			return (1);
		if (is_token((char *)tmp->content) && is_token((char *)tmp->next->content))
			return (1);
		if (ft_strcmp((char *)tmp->content, "<") == 0)
			data->infile = (char *)tmp->next->content;
		if (!ft_strcmp((char *)tmp->content, ">"))
			data->outfile = (char *)tmp->next->content;
		if (!ft_strcmp((char *)tmp->content, "<<"))
			data->delimitor = (char *)tmp->next->content;
		if (!ft_strcmp((char *)tmp->content, ">>"))
			data->append = 1;
		tmp = tmp->next;
	}
	return (0);
}

void	built_in_tokenisation(t_list *list)
{
	t_list *tmp;

	tmp = list;
	while (tmp)
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

int	analyzer(t_data *data, t_cmd *cmd)
{
	if (get_redir_file(&data->list, data))
		return (on_error("Minishell: syntax error near unexpected token\n", 1));
	redir_tokenisation(data->list);
	built_in_tokenisation(data->list);
	get_cmd_size(data->list, data);
	get_cmd_count(data->list, data);
	// code the redirections before removing thems
	//redirect_in(data);
	ft_print_list(data->list);
	printf("-----------\n");
	// boucler du nombre de redirection trouver pour toutes les remoove
	remove_redir(&data->list);
	printf("-----------\n");
	ft_print_list(data->list);
	// boucler du nombre de commandes => get_cmd puis remove first pipe found, repeat for each cmd
	get_cmd_from_list(&data->list, data, cmd);
	remove_pipe(&data->list);
	printf("-----------\n");
	ft_print_list(data->list);
	exec_command(cmd, data);
	return (0);
}