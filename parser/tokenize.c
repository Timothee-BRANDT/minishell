/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:42:43 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/04 15:03:28y tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redir_tokenisation(t_list *list)
{
	t_list *tmp;

	tmp = list;
	while (tmp && tmp->next)
	{
		if (ft_strcmp((char *)list->content, "<") == 0)
			list->token = REDIR_IN;
		if (ft_strcmp((char *)list->content, ">") == 0)
			list->token = REDIR_OUT;
		if (ft_strcmp((char *)list->content, "<<") == 0)
			list->token = DELIM;
		if (ft_strcmp((char *)list->content, ">>") == 0)
			list->token = APPEND;
		if (ft_strcmp((char *)list->content, "|") == 0)
			list->token = PIPE;
		list = list->next;
		tmp = list;
	}
}

int	get_redir_file(t_list *list, t_data *data)
{
	t_list *tmp;

	if (!list)
		return (0);
	tmp = list;
	while (tmp && tmp->next)
	{
		if (is_token((char *)tmp->next->content) && !tmp->next->next)
			return (1);
		if (is_token((char *)tmp->content) && is_token((char *)tmp->next->content))
			return (1);
		if (ft_strcmp((char *)tmp->content, "<") == 0)
			data->infile = ft_strdup((char *)tmp->next->content);
		if (!ft_strcmp((char *)tmp->content, ">"))
			data->outfile = ft_strdup((char *)tmp->next->content);
		if (!ft_strcmp((char *)tmp->content, "<<"))
			data->delimitor = ft_strdup((char *)tmp->next->content);
		if (!ft_strcmp((char *)tmp->content, ">>"))
			data->append = 1;
		tmp = tmp->next;
	}
	return (0);
}

void	built_in_tokenisation(t_list *list)
{
	t_list *tmp;

	tmp = list;
	while (tmp && tmp->next)
	{
		if (!ft_strcmp((char *)list->content, "echo") || !ft_strcmp((char *)list->content, "ECHO"))
			list->token = ECHO;
		if (!ft_strcmp((char *)list->content, "cd") || !ft_strcmp((char *)list->content, "CD"))
			list->token = CD;
		if (!ft_strcmp((char *)list->content, "pwd") || !ft_strcmp((char *)list->content, "PWD"))
			list->token = PWD;
		if (!ft_strcmp((char *)list->content, "export") || !ft_strcmp((char *)list->content, "EXPORT"))
			list->token = EXPORT;
		if (!ft_strcmp((char *)list->content, "unset") || !ft_strcmp((char *)list->content, "UNSET"))
			list->token = UNSET;
		if (!ft_strcmp((char *)list->content, "env") || !ft_strcmp((char *)list->content, "ENV"))
			list->token = ENV;
		if (!ft_strcmp((char *)list->content, "exit") || !ft_strcmp((char *)list->content, "EXIT"))
			list->token = EXIT;
		list = list->next;
		tmp = list;
	}
}

void	forking(t_cmd *cmd, t_data *data)
{
	pid_t pid;
	
	pid = fork();
	if (pid == 0)
		exec_command(cmd, data);
	waitpid(pid, NULL, 0);
}


int	start_exec(t_cmd *cmd, t_data *data)
{
	int i;
	int	pipe_fd[2];

	i = -1;
	while (++i < data->cmd_count)
	{
		if (i == data->cmd_count - 1)
		{
			if (data->outfile)	
			{
				data->fd_out = open(data->outfile, O_RDWR | O_CREAT | O_NOCTTY | \
				O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
				free(data->outfile);
				data->outfile = NULL;
				remove_out_redir(data->list);
			}
			else
				data->fd_out = dup(data->tmp_out);
		}
		else
		{
			pipe(pipe_fd);
			data->fd_out = pipe_fd[1];
			data->fd_in = pipe_fd[0];
			dup2(data->fd_in, 0);
			close(data->fd_in);
		}
		dup2(data->fd_out, 1);
		close(data->fd_out);
		get_cmd_from_list(data->list, data, cmd);
		remove_pipe(data->list);
		forking(cmd, data);
	}
	dup2(data->tmp_in, 0);
	close(data->tmp_in);
	dup2(data->tmp_out, 1);
	close(data->tmp_out);
	return (0);
}

int	analyzer(t_data *data, t_cmd *cmd)
{
	if (get_redir_file(data->list, data))
		return (on_error("Minishell: syntax error near unexpected token\n", 1));
	redir_tokenisation(data->list);
	built_in_tokenisation(data->list);
	get_cmd_size(data->list, data);
	get_cmd_count(data->list, data);
	if (check_in_redirection(data->list, data))
		return (open_error(data->infile));

	start_exec(cmd, data);
	//if (check_out_redirection(data->list, data))
	//	return (open_error(data->outfile));
	//forking(cmd, data);
	return (0);
}