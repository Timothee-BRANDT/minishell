/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:11:22 by tbrandt           #+#    #+#             */
/*   Updated: 2022/09/28 14:48:49 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    remove_redir(t_list **list)
{
	t_list	*tmp;
	t_list	*redir;
	t_list	*redir_arg;

	tmp = *list;
	while(tmp->next)
	{
		if (is_redir((char *)tmp->next->content) && (*list)->next->next)
		{
			redir = tmp->next;
			redir_arg = tmp->next->next;
			tmp->next = tmp->next->next->next;
			if (redir->content)
				free(redir->content);
			if (redir_arg->content)
				free(redir_arg->content);
			free(redir);
			free(redir_arg);
		}
		tmp = tmp->next;
    }
}

void    remove_pipe(t_list **list)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (is_pipe((char *)tmp->content) && tmp->next)
			*list = (*list)->next;
		tmp = tmp ->next;
	}
}
/*void    remove_pipe(t_list *list)
{
	t_list	*tmp;
	t_list	*pipe;

	tmp = list;
	while(tmp->next)
	{
		if (is_pipe((char *)list->content) && list->next)
		{
			pipe = list->next;
			tmp = tmp->next;
		}
		if (is_pipe((char *)list->next->content) && list->next->next)
		{
			pipe = list->next;
			list->next = list->next->next;
			if (pipe->content)
				free(pipe->content);
			free(pipe);
		}
		if (list->next)
			list = list->next;
		tmp = list;
    }
}*/