/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:01:36 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/16 16:18:35by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	append_or_not(int	*k, char **cmd, t_data *data, int code)
{
	if (code == 0)
	{
		if (data->append == 1)
			data->fd_out = open(cmd[*k + 1], O_WRONLY | O_CREAT | O_APPEND | O_NOCTTY , \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else
		{
			data->fd_out = open(cmd[*k + 1], O_WRONLY | O_CREAT | O_NOCTTY , \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		}
	}
	else
	{
		if (data->append == 1)
			data->last_redir = open(cmd[*k - 1], O_WRONLY | O_CREAT | O_APPEND |  O_NOCTTY , \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else
			data->last_redir = open(cmd[*k - 1], O_WRONLY | O_CREAT |  O_NOCTTY, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
}

void    redir_out_manager(int *k, char **cmd, t_data *data)
{
	data->check_fd_out = 1;
	data->append = 0;
	if (cmd[*k] && cmd[*k][1] == '>')
		data->append = 1;
	append_or_not(k, cmd, data, 0);
	*k = *k + 2;
	if (!cmd[*k] && *k == ft_strlen2d(cmd))
	{
		data->last_cmd = 1;
		append_or_not(k, cmd, data, 1);
	}
	if (cmd[*k] && cmd[*k][1] == '>')
		data->append = 1;
	while (cmd[*k] && (!ft_strcmp(cmd[*k], ">") || !ft_strcmp(cmd[*k], ">>")))
	{
		append_or_not(k, cmd, data, 0);
		*k = *k + 2;
		if (!cmd[*k] && *k == ft_strlen2d(cmd))
		{
			data->last_cmd = 1;
			append_or_not(k, cmd, data, 1);
		}
		if (cmd[*k] && cmd[*k][1] == '>')
			data->append = 1;
		else
			data->append = 0;
    }
}

int	redir_in_manager(int	*k, char **cmd, t_data *data)
{
	data->check_fd_in = 1;
	if (!ft_strcmp(cmd[*k], "<"))
	{
		data->fd_in = open(cmd[*k + 1], O_RDONLY);
		*k = *k +2;
	}
	while (cmd[*k] && (!ft_strcmp(cmd[*k], "<")))
	{
		data->fd_in = open(cmd[*k + 1], O_RDONLY);
		*k = *k +2;
	}
	return (0);
}