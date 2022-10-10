/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:16:10 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/07 11:34:42by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    restore_fd(t_data *data)
{
	dup2(data->tmp_in, 0);
	close(data->tmp_in);
	dup2(data->tmp_out, 1);
	data->fdd = 0;
}

void	create_pipe(t_data *data)
{
	int pipe_fd[2];

	pipe(pipe_fd);
	data->fd_out = pipe_fd[1];
	data->fd_in = pipe_fd[0];
}

void    dup_child_exec(char **cmds, t_data *data)
{
	dup2(data->fdd, 0);
	dup2(data->fd_out, 1);
    exec_command(cmds, data);
	exit(0);
}

void	dup_parent(t_data *data)
{
	close(data->fd_out);
	data->fdd = data->fd_in;
}

void	redir_fd_out(t_data *data)
{
	if (data->outfile)	
	{
		data->fd_out = open(data->outfile, O_WRONLY | O_CREAT | O_NOCTTY | \
		O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		free(data->outfile);
		data->outfile = NULL;
		remove_out_redir(data->list);
	}
	else
		data->fd_out = dup(data->tmp_out);
}