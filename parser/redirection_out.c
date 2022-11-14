/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_out.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 15:39:09 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/14 14:43:41 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_all_infile(t_list *list, t_data *data)
{
	t_list	*tmp;

	tmp = list;
	while (tmp && tmp->next)
	{
		if (!ft_strcmp((char *)tmp->content, "<"))
		{
			data->check_fd = open((char *)tmp->next->content, O_RDONLY);
			close(data->check_fd);
			if (data->check_fd == -1)
			{
				data->check_fd = 0;
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

void	redir_fd_out(t_data *data)
{
	if (data->last_cmd)
	{
		data->last_cmd = 0;
		data->fd_out = dup(data->last_redir);
	}
	else if (!data->check_fd_out)
	{
		data->fd_out = dup(data->tmp_out);
		close(data->tmp_out);
	}
}
