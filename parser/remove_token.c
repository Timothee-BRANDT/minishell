/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:11:22 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/01 17:05:00y tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	free_redir(t_list *redir, t_list *redir_arg)
{

	if (redir->content)
		free(redir->content);		
	if (redir_arg->content)
		free(redir_arg->content);
	free(redir);
	free(redir_arg);
}

void	redir_norm(t_list *tmp, t_list *redir, t_list *redir_arg)
{
	redir = tmp->next;
	redir_arg = tmp->next->next;
	if (tmp->next->next->next != NULL)
	{
		tmp->next = tmp->next->next->next;
		free_redir(redir, redir_arg);
	}
	else
		tmp->next = NULL;
}

void	redir_norm1(t_list *list, t_list *redir, t_list *redir_arg, t_list *tmp)
{
	redir = tmp;
	redir_arg = tmp->next;
	if (tmp->next != NULL)
	{
		list = tmp->next->next;
		free_redir(redir, redir_arg);
	}
}

void    remove_in_redir(t_list *list)
{
	t_list	*tmp;
	t_list	*redir;
	t_list	*redir_arg;
	int i;

	tmp = list;
	redir = NULL;
	redir_arg = NULL;
	i = 0;
	while(tmp && tmp->next)
	{
		if ((is_redir((char *)tmp->content) == 3) && tmp->next && i == 0)
		{
			redir_norm1(tmp, redir, redir_arg, tmp);
			i = 1;
			break ;
		}
		else if ((is_redir((char *)tmp->next->content) == 3) && tmp->next->next)
		{
			redir_norm(tmp, redir, redir_arg);
			break ;
		}
		tmp = tmp->next;
    }
}

void    remove_out_redir(t_list *list)
{
	t_list	*tmp;
	t_list	*redir;
	t_list	*redir_arg;
	int i;

	tmp = list;
	redir = NULL;
	redir_arg = NULL;
	i = 0;
	while(tmp && tmp->next)
	{
		if ((is_redir((char *)tmp->content) == 4) && tmp->next && i == 0)
		{
			redir_norm1(tmp, redir, redir_arg, tmp);
			i = 1;
			break ;
		}
		else if ((is_redir((char *)tmp->next->content) == 4) && tmp->next->next)
		{
			redir_norm(tmp, redir, redir_arg);
			break ;
		}
		tmp = tmp->next;
	}
}

void    remove_pipe(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp && tmp->next)
	{
		if (is_pipe((char *)tmp->content) && tmp->next)
		{
			(*list) = *tmp;
			break ;
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
}

// need to free the link i skipped
void	remove_args(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp->next)
	{
		if (is_pipe((char *)tmp->next->content))
		{
			(*list) = *tmp->next->next;
			break ;
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
}