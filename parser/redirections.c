/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:55:00 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/02 15:14:42brandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_redir_in(t_list *list)
{
	t_list	*tmp;
	int		count;

	tmp = list;
	count = 0;
	while (tmp && tmp->next)
	{
		if (tmp->token == 1)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

int	check_in_redirection(t_list *list, t_data *data)
{
	t_list *tmp;
	int		redir_count;
	int		j;

	tmp = list;
	redir_count = count_redir_in(list);
	j = -1;
	data->tmp_in = dup(0);
	data->tmp_out = dup(1);
	get_first_redir_in(list, data);
	while (tmp && tmp->next)
	{
		if (tmp->token == 1)
		{
			while (++j < redir_count)
			remove_in_redir(data->list);
			if (redirect_in(data))
				return (1);
			break ;
		}
		tmp = tmp->next;
	}
	 return (0);
}

/*int	get_first_redirection(t_list *list, t_data *data)
{
	t_list *tmp;

	tmp = list;
	dprintf(data->tmp_out, "3\n");
	while (tmp && tmp->next && ft_strcmp((char *)tmp->content, "|") != 0)
	{
		dprintf(data->tmp_out, "4\n");
		if (tmp && tmp->next && tmp->next->next && !ft_strcmp((char *)tmp->content, ">") && !ft_strcmp((char *)tmp->next->next->content, "|"))
		{
			dprintf(data->tmp_out, "5\n");
			data->first_outfile = ft_strdup((char *)tmp->next->content);
		}
		dprintf(data->tmp_out, "6\n");
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	dprintf(data->tmp_out, "7\n");
	return (0);
}*/

/*int get_first_redirection_before_pipe(t_data *data)
{
	char	**tab;
	int		i;

	tab = lst_to_tab(data->list, data);
	i = 0;
	while (tab[i] && ft_strcmp(tab[i], "|") != 0)
	{
		if (!ft_strcmp(tab[i], ">") && tab[i + 2] && !ft_strcmp(tab[i + 2], "|"))
			data->first_outfile = ft_strdup(tab[i + 1]);
		i++;
	}
	free_tab(tab);
	if (data->first_outfile)
		return (1);
	return (0);
}

int	check_out_redirection_before_pipe(t_list *list, t_data *data)
{
	t_list *tmp;

	tmp = list;
	while (tmp && tmp->next && ft_strcmp((char *)tmp->content, "|") != 0)
	{
		if (ft_strcmp((char *)tmp->content, ">") == 0)
		{
			data->fd_out = open(data->first_outfile, O_WRONLY | O_CREAT | O_NOCTTY | \
			O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			dprintf(data->tmp_out, "first_outfile: %s\n", data->first_outfile);
			free(data->first_outfile);
			data->first_outfile = NULL;
			remove_out_redir(data->list);
			data->first_redir_check = 1;
			break;
		}
		tmp = tmp->next;
	}
	return (0);
}*/

int	redirect_in(t_data *data)
{
	data->fd_in = 0;
	if (data->infile)
	{
		data->fd_in = open(data->infile, O_RDONLY);
		free(data->infile);
		data->infile = NULL;
		if (data->fd_in == -1)
			return (1);
	}
	else
		data->fd_in = dup(data->tmp_in);
	dup2(data->fd_in, 0);
	close(data->fd_in);
	return (0);
}