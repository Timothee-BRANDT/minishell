/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:39:09 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/18 14:28:13 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_all_infile(t_list *list, t_data *data)
{
	t_list *tmp;

	tmp = list;
	while (tmp && tmp->next)
	{
		if (!ft_strcmp((char *)tmp->content, "<"))
		{
			data->check_fd = open((char *)tmp->next->content, O_RDONLY);
			close(data->check_fd);
			if (data->check_fd == - 1)
			{
				data->check_fd = 0;
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	get_first_redir_out(t_list *list, t_data *data)
{
	t_list *tmp;

	if (!list)
		return (0);
	tmp = list;
	while (tmp && tmp->next)
	{
		if (!ft_strcmp((char *)tmp->content, ">"))
		{
			if (data->outfile)
				free(data->outfile);
			data->outfile = ft_strdup((char *)tmp->next->content);
		}
		tmp = tmp->next;
	}
	return (0);	
}

int	get_redir_count(t_list *list)
{
	t_list 	*tmp;
	int		redir_out_count;

	tmp = list;
	redir_out_count = 0;
	while (tmp && tmp->next)
	{
		if (!ft_strcmp((char *)tmp->content, ">") || !ft_strcmp((char *)tmp->content, ">"))
			redir_out_count++;
		tmp = tmp->next;
	}
	return (redir_out_count);
}

void	redir_fd_out(t_data *data)
{
	int	redir_count;
	int	i;

	redir_count = get_redir_count(data->list);
	i = -1;
	get_first_redir_out(data->list, data);
	if (data->outfile && data->out_before_pipe == 0)
	{
		while (++i < redir_count)
			get_fd_and_free(data->list, data);
	}
	else if (data->last_cmd)
	{
		data->last_cmd = 0;
		data->fd_out = dup(data->last_redir);
	}
	else
	{
		data->fd_out = dup(data->tmp_out);
		data->out_before_pipe = 0;
	}
}

void	get_fd_and_free(t_list *list, t_data *data)
{
	if (data->append == 1)
	{
		data->fd_out = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND | O_NOCTTY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		free(data->outfile);
		data->outfile = NULL;
		get_first_redir_out(list, data);
	}
	else
	{
		data->fd_out = open(data->outfile, O_WRONLY | O_CREAT | O_NOCTTY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		free(data->outfile);
		data->outfile = NULL;
		get_first_redir_out(list, data);
	}
}