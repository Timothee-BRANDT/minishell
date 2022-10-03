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

int	check_in_redirections(t_list *list, t_data *data)
{
	t_list *tmp;

	tmp = list;
	while (tmp && tmp->next)
	{
		if (tmp->token == 1)
		{
			data->restore_in_redir = 1;
			remove_redir(data->list);
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
	int	fd_in;

	data->tmp_in = dup(0);
	data->tmp_out = dup(1);
	fd_in = 0;
	if (data->infile)
	{
		fd_in = open(data->infile, O_RDONLY);
		if (fd_in == -1)
			return (1);
	}
	else
		fd_in = dup(data->tmp_in);
	dup2(fd_in, 0);
	close(fd_in);
	return (0);
}

void	restore_in_redir(t_data *data)
{
	dup2(data->tmp_in, 0);
	close(data->tmp_in);
}
/*void	redirect_out(t_data *data)
{
	printf("let's do the out redirection\n");
}

void	redirect_in_delim(t_data *data)
{
	printf("let's do the in_delimitor redirection\n");
}

void	redirect_out_append(t_data *data)
{
	printf("let's do the out_append redirection\n");
}*/