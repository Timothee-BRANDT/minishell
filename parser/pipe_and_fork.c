/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:16:10 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/21 09:10:50y tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipe(t_data *data)
{
	int pipe_fd[2];

	pipe(pipe_fd);
	data->pipe_1 = pipe_fd[1]; // output
	data->pipe_0 = pipe_fd[0]; // input
}

void    dup_child_exec(char **cmds, t_data *data, int cmd_count)
{
	if (data->check_fd_in == 1)
	{
		dup2(data->fd_in, 0);
		dprintf(data->tmp_out, "IN CHILD ------fd_in: %d\n", data->fd_in);
		close(data->fd_in);
		dprintf(data->tmp_out, "IN CHILD AFTER CLOSING ------fd_in: %d\n", data->fd_in);
	}
	if (data->check_fd_out == 1)
	{
		dup2(data->fd_out, 1);
		dprintf(data->tmp_out, "----------------------IN CHILD ------fd_out: %d\n", data->fd_out);
		close(data->fd_out);
	}
	else if (cmd_count > 1)
	{
		close(data->pipe_0);
		dup2(data->pipe_1, 1);
		close(data->pipe_1);
	}
	exec_command(cmds, data);
	exit(0);
}

void	dup_parent(t_data *data, int cmd_count)
{
	if (cmd_count > 1)
	{
		dup2(data->pipe_0, 0);
		close(data->pipe_0);
	}
	close(data->pipe_1);
}


int	wait_my_childs(t_data *data)
{
	int	i;
	int status;

	status = 0;
	i = -1;
	while (++i < data->cmd_count)
		waitpid(0 , &status, 0);
	return (0);
}

void    restore_fd(t_data *data)
{
	close(data->last_redir);
	close(data->fd_in);
	close(data->fd_out);
	dup2(data->tmp_in, 0);
	close(data->tmp_in);
	dup2(data->tmp_out, 1);
	close(data->tmp_out);
}