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

int	get_first_redir_in(t_list *list, t_data *data)
{
    t_list *tmp;

    tmp = list;
    while (tmp && tmp->next)
    {
        if (!ft_strcmp((char *)tmp->content, "<"))
        {
            if (data->infile)
                free(data->infile);
            data->infile = ft_strdup((char *)tmp->next->content);
        }
        tmp = tmp->next;
    }
    return (0);	
}
