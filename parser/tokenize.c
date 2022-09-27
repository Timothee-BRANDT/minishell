/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:42:43 by tbrandt           #+#    #+#             */
/*   Updated: 2022/09/27 12:45:13 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	get_redir_file(t_list *cmd, t_data *data)
{
	t_list *tmp;

	tmp = cmd;
	while (tmp)
	{
		if (is_token((char *)cmd->content) && !cmd->next)
			return (1);
		if (!ft_strcmp((char *)cmd->content, "<"))
			data->infile = (char *)data->cmd->next->content;
		if (!ft_strcmp((char *)cmd->content, ">"))
			data->outfile = (char *)data->cmd->next->content;
		if (!ft_strcmp((char *)cmd->content, "<<"))
			data->delimitor = (char *)data->cmd->next->content;
		if (!ft_strcmp((char *)cmd->content, ">>"))
			data->append = 1;
		cmd = cmd->next;
		tmp = cmd;
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
	if (get_redir_file(data->cmd, data))
		return (on_error("Minishell: syntax error near unexpected token `newline'\n", 1));
	redir_tokenisation(data->cmd);
	built_in_tokenisation(data->cmd);
	built_in_analyzer(cmd, data);
	ft_print_list(data->cmd);
	printf("\n");
	// faire une boucle du nombre de tokens a retirer dans la liste, si 4 token a retirer, remove_token * 4;
	// faire une fonction qui recupere la commande dans un char ** avant un token redir ou pipe, pour chqaue commande, dans une boucle du nombre de commandes
	// 1) stocker la commande 2)analyse des redir et pipe 3)remove les tokens
	//remove_redir(data->cmd);
	//remove_pipe(data->cmd);
	get_cmd_count(data->cmd, data);
	get_cmd_from_list(data->cmd, data);
	//exec_command(cmd, data);
	return (0);
}