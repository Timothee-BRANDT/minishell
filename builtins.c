/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:31:02 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/14 16:50:38 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*env_to_list(char **env)
{
	t_list *list;
	int		i;

	i = 1;
	list = ft_lstnew(env[0]);
	while (env[i])
	{
		ft_lstadd_back(&list, ft_lstnew(env[i]));
		i++;
	}
	return (list);
}

void	unset_name(t_list **list, char *name)
{
	t_list	*ptr;
	t_list	*tmp;
	int		len;

	tmp = NULL;
	ptr = *list;
	len = ft_strlen(name);
	while(ptr->next != NULL)
	{
		if (ft_strncmp((char *)(ptr->next->content), name, len) == 0)
		{
			tmp = ptr->next;
			ptr->next = ptr->next->next;
			free(tmp);
		}
		ptr = ptr->next;
	}
}