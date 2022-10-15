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
	close(data->fd_out);
	data->fdd = 0;
}

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

int	get_redir_count(t_list *list)
{
	t_list 	*tmp;
	int		redir_out_count;

	tmp = list;
	redir_out_count = 0;
	while (tmp && tmp->next)
	{
		if (ft_strcmp((char *)tmp->content, ">") == 0)
			redir_out_count++;
		tmp = tmp->next;
	}
	return (redir_out_count);
}

void	free_2_tab(char **tab1, char **tab2)
{
	free_tab(tab1);
	free_tab(tab2);
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

void	get_fd_and_free(t_list *list, t_data *data)
{
	data->fd_out = open(data->outfile, O_WRONLY | O_CREAT | O_NOCTTY | \
	O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	free(data->outfile);
	data->outfile = NULL;
	get_first_redir_out(list, data);

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
