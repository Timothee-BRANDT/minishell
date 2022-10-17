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

void	redir_norm(t_list *tmp)
{
	t_list *redir;
	t_list *redir_arg;

	redir = tmp->next;
	redir_arg = tmp->next->next;
	if (tmp->next->next->next)
	{
		tmp->next = tmp->next->next->next;
		free(redir->content);		
		free(redir);
		free(redir_arg->content);
		free(redir_arg);
	}
	else
	{
		tmp->next = NULL;
		free(redir->content);
		free(redir);
		free(redir_arg->content);
		free(redir_arg);
	}
}

void	redir_norm1(t_list *tmp)
{
	t_list	*redir;
	t_list	*redir_arg;

	redir = tmp;
	redir_arg = tmp->next;
	if (tmp->next && tmp->next->next)
	{
		tmp = tmp->next->next;
		ft_print_list(tmp);
		//free(redir->content);		
		//free(redir);
		//free(redir_arg->content);
		//free(redir_arg);
	}
}

void	remove_in_redir(t_list *list)
{
	t_list	*tmp;
	int i;

	tmp = list;
	i = 0;
	while(tmp && tmp->next)
	{
		if ((is_redir((char *)tmp->content) == 3) && tmp->next && i == 0)
		{
			redir_norm1(tmp);
			i = 1;
			break ;
		}
		else if ((tmp->next && is_redir((char *)tmp->next->content) == 3) && tmp->next->next)
		{
			redir_norm(tmp);
			break ;
		}
		tmp = tmp->next;
    }
}