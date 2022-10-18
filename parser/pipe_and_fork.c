/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:16:10 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/18 18:29:17 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipe(t_data *data)
{
	int pipe_fd[2];

	pipe(pipe_fd);
	if (data->out_before_pipe == 1)
	{
		dup2(data->fd_out, 1);
		close(data->fd_out);
		close(pipe_fd[1]);
	}
	else
		data->fd_out = pipe_fd[1];
	if (data->check_fd_in == 0)
		data->fd_in = pipe_fd[0];
	data->check_fd_in = 0;
}

void    dup_child_exec(char **cmds, t_data *data)
{
	dup2(data->fd_in , 0);
	dup2(data->fd_out, 1);
	exec_command(cmds, data);
	exit(0);
}

void	dup_parent(t_data *data)
{
	close(data->fd_out);
//	data->fdd = data->fd_in;
}


int	wait_my_childs(t_data *data)
{
	int	i;
	int status;

	status = 0;
	i = -1;
	while (++i < data->cmd_count)
		waitpid(0 , &status, WUNTRACED);
	return (0);
}

void    restore_fd(t_data *data)
{
	dup2(data->tmp_in, 0);
	close(data->tmp_in);
	dup2(data->tmp_out, 1);
	close(data->fd_out);
	data->fdd = 0;
}