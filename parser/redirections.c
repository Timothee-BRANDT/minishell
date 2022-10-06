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
	int		i;
	int		j;

	tmp = list;
	i = count_redir_in(list);
	j = -1;
	data->tmp_in = dup(0);
	data->tmp_out = dup(1);
	while (tmp && tmp->next)
	{
		if (tmp->token == 1)
		{
			data->restore_in_redir = 1;
			while (++j < i)
				remove_in_redir(data->list);
			if (redirect_in(data))
				return (1);
			break ;
		}
		tmp = tmp->next;
	}
	 return (0);
}

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

/*int check_out_redirection(t_list *list, t_data *data)
{
	t_list *tmp;

	tmp = list;
	while (tmp && tmp->next)
	{
		if (tmp->token == 2)
		{
			data->restore_out_redir = 1;
			remove_out_redir(data->list);
			if (redirect_out(data))
				return (1);
			break ;
		}
		tmp = tmp->next;
	}
	return (0);
}

 useless function i guess
int	redirect_out(t_data *data)
{
	int	fd_out;

	data->tmp_in = dup(0);
	data->tmp_out = dup(1);	
	fd_out = 0;
	if (data->outfile)
	{
		fd_out = open(data->outfile, O_RDWR | O_CREAT | O_NOCTTY | \
		O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd_out == -1)
			return (1);
	}
	else
		fd_out = dup(data->tmp_out);
	dup2(fd_out, 1);
	close(fd_out);
	return (0);
}*/

void	restore_redir(t_data *data, int code)
{
	if (code == REDIR_IN)
	{
		dup2(data->tmp_in, 0);
		close(data->tmp_in);
		data->restore_in_redir = 0;
	}
	else if (code == REDIR_OUT)
	{
		dup2(data->tmp_out, 1);
		close(data->tmp_out);
		data->restore_out_redir = 0;
	}
}
/*
void	redirect_in_delim(t_data *data)
{
	printf("let's do the in_delimitor redirection\n");
}

void	redirect_out_append(t_data *data)
{
	printf("let's do the out_append redirection\n");
}*/