/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:42:43 by tbrandt           #+#    #+#             */
/*   Updated: 2022/09/26 14:51:13 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_in_analyzer(t_list **cmd, t_data	*data)
{
	if (!(*cmd))
		return ;
    if (is_built_in((*cmd)->content))
    {
		if (ft_strcmp((*cmd)->content, "env") == 0)
			ft_print_env(data->env);
		if (ft_strcmp((*cmd)->content, "export") == 0 && !data->cmd->next)
			ft_print_env(data->export);
		if (ft_strcmp((*cmd)->content, "export") == 0 && data->cmd->next)
			export_name(cmd, data, 0);
		if (ft_strcmp((*cmd)->content, "unset") == 0 && (*cmd)->next)
    	{
    		unset_name_export(&data->export, cmd);
    		unset_name_env(&data->env, cmd);
		}
	}
}

void	redir_tokenisation(t_list *cmd)
{
	t_list *tmp;

	tmp = cmd;
	while (tmp)
	{
		if (ft_strcmp((char *)cmd->content, "<") == 0)
			cmd->token = TOKEN_REDIR_IN;
		if (ft_strcmp((char *)cmd->content, ">") == 0)
			cmd->token = TOKEN_REDIR_OUT;
		if (ft_strcmp((char *)cmd->content, "<<") == 0)
			cmd->token = TOKEN_DELIM;
		if (ft_strcmp((char *)cmd->content, ">>") == 0)
			cmd->token = TOKEN_REDIR_APPEND;
		if (ft_strcmp((char *)cmd->content, "|") == 0)
			cmd->token = TOKEN_PIPE;
		cmd = cmd->next;
		tmp = cmd;
	}
}

int	get_redir_file(t_data *data)
{
	t_list *tmp;

	tmp = data->cmd;
	while (tmp)
	{
		if (is_token((char *)data->cmd->content) && !data->cmd->next)
			return (1);
		if (!ft_strcmp((char *)data->cmd->content, "<"))
			data->infile = (char *)data->cmd->next->content;
		if (!ft_strcmp((char *)data->cmd->content, ">"))
				data->outfile = (char *)data->cmd->next->content;
		if (!ft_strcmp((char *)data->cmd->content, "<<"))
				data->delimitor = (char *)data->cmd->next->content;
		if (!ft_strcmp((char *)data->cmd->content, ">>"))
				data->append = 1;
		data->cmd = data->cmd->next;
		tmp = data->cmd;
	}
	return (0);
}

void	built_in_tokenisation(t_list *cmd)
{
	t_list *tmp;

	tmp = cmd;
	while (tmp)
	{
		if (!ft_strcmp((char *)cmd->content, "echo") || !ft_strcmp((char *)cmd->content, "ECHO"))
			cmd->token = ECHO;
		if (!ft_strcmp((char *)cmd->content, "cd") || !ft_strcmp((char *)cmd->content, "CD"))
			cmd->token = CD;
		if (!ft_strcmp((char *)cmd->content, "pwd") || !ft_strcmp((char *)cmd->content, "PWD"))
			cmd->token = PWD;
		if (!ft_strcmp((char *)cmd->content, "export") || !ft_strcmp((char *)cmd->content, "EXPORT"))
			cmd->token = EXPORT;
		if (!ft_strcmp((char *)cmd->content, "unset") || !ft_strcmp((char *)cmd->content, "UNSET"))
			cmd->token = UNSET;
		if (!ft_strcmp((char *)cmd->content, "env") || !ft_strcmp((char *)cmd->content, "ENV"))
			cmd->token = ENV;
		if (!ft_strcmp((char *)cmd->content, "exit") || !ft_strcmp((char *)cmd->content, "EXIT"))
			cmd->token = EXIT;
		cmd = cmd->next;
		tmp = cmd;
	}
}



int	analyzer(t_list **cmd, t_data *data)
{
	if (get_redir_file(data))
		return (on_error("Minishell: syntax error near unexpected token `newline'", 1));
	redir_tokenisation(data->cmd);
	built_in_tokenisation(data->cmd);
	built_in_analyzer(cmd, data);
	//exec_command(cmd, data);
	return (0);
}