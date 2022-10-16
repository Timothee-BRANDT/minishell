/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:01:36 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/16 15:25:58 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    redir_out_manager(int *k, char **cmd, t_data *data)
{
	if (cmd[*k][1] == '>')
		data->append = 1;
	if (data->append == 1)
		data->fd_out = open(cmd[*k + 1], O_WRONLY | O_CREAT | O_APPEND | O_NOCTTY , \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		data->fd_out = open(cmd[*k + 1], O_WRONLY | O_CREAT | O_NOCTTY , \
		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	*k = *k + 2;
	if (cmd[*k] && !ft_strcmp(cmd[*k], "|"))
		data->out_before_pipe = 1;
	// last command
	if (!cmd[*k] && *k == ft_strlen2d(cmd))
	{
		data->last_cmd = 1;
		if (data->append == 1)
			data->last_redir = open(cmd[*k - 1], O_WRONLY | O_CREAT | O_APPEND |  O_NOCTTY , \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else
			data->last_redir = open(cmd[*k - 1], O_WRONLY | O_CREAT |  O_NOCTTY, \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	}
	// boucle sur >> 1 >> 2 >> 3 >> 4
	while (cmd[*k] && !ft_strcmp(cmd[*k], ">"))
	{
		if (data->append == 1)
			data->fd_out = open(cmd[*k + 1], O_WRONLY | O_CREAT | O_APPEND | O_NOCTTY , \
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		else
			data->fd_out = open(cmd[*k + 1], O_WRONLY | O_CREAT  | O_NOCTTY , S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		*k = *k + 2;
		if (cmd[*k] && cmd[*k][1] == '>')
			data->append = 1;
		else
			data->append = 0;
    }
}