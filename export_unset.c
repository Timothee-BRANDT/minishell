/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:31:02 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/15 12:13:34 by tbrandt          ###   ########.fr       */
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

void	export_name(t_list **env, t_list **export, char *name)
{
	int	i;
	int	check;
	
	i = 0;
	check = 0;
	if (!(*env) || !(*export))
		return;
	while(name[i])
	{
		if (name[i] == '=')
			check = 1;
		i++;
	}
	if (check == 1)
	{
		ft_lstadd_back(export, ft_lstnew((void *)name));
		ft_lstadd_back(env, ft_lstnew((void *)name));
	}
	else
		ft_lstadd_back(export, ft_lstnew((void *)name));
}

void	unset_name_env(t_list **env, char *name)
{
	t_list	*ptr;
	t_list	*tmp;
	int		len;

	ptr = *env;
	len = ft_strlen(name);
	while (ptr->next != NULL)
	{
		if (ft_strncmp((char *)(ptr->next->content), name, len) == 0)
		{
			tmp = ptr->next;
			ptr->next = ptr->next->next;
			free(tmp);
			if (!ptr->next)
				return ;
		}
		ptr = ptr->next;
	}
}

void	unset_name_export(t_list **export, char *name)
{
	t_list	*ptr;
	t_list	*tmp;
	int		len;

	ptr = *export;
	len = ft_strlen(name);
	while (ptr->next != NULL)
	{
		if (ft_strncmp((char *)(ptr->next->content), name, len) == 0)
		{
			tmp = ptr->next;
			ptr->next = ptr->next->next;
			free(tmp);
			if (!ptr->next)
				return ;
		}
		ptr = ptr->next;
	}
}
