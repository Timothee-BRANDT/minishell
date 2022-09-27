/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:11:22 by tbrandt           #+#    #+#             */
/*   Updated: 2022/09/27 11:17:37 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    remove_redir(t_list *cmd)
{
	t_list *tmp;
	int next;

	tmp = cmd;
	next = 0;
	while(tmp->next)
	{
		if (is_redir((char *)cmd->next->content) && cmd->next->next)
			cmd->next = cmd->next->next->next;
		if (cmd->next)
			cmd = cmd->next;
		tmp = cmd;
    }
}

void    remove_pipe(t_list *cmd)
{
	t_list *tmp;
	int next;

	tmp = cmd;
	next = 0;
	while(tmp->next)
	{
		if (is_pipe((char *)cmd->next->content) && cmd->next->next)
			cmd->next = cmd->next->next;
		if (cmd->next)
			cmd = cmd->next;
		tmp = cmd;
    }
}