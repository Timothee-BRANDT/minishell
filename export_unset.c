/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:31:02 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/15 17:18:41 by tbrandt          ###   ########.fr       */
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

int	is_in_list(t_list **list, char *name)
{
	t_list	*ptr;

	ptr = *list;
	while(ptr->next != NULL)
	{
		if (ft_strcmp(ft_get_name((char *)(ptr->next->content)), name) == 0)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

void	found_and_replace(t_list **export, char *name)
{
	t_list	*ptr;

	ptr = *export;
	while (ptr)
	{
		if (ft_strcmp(ft_get_name((char *)(ptr->next->content)), ft_get_name(name)) == 0)
		{
			printf("ptr->next->content :%s\n", ptr->next->content);
			free(ptr->next);
			ptr->next = ft_lstnew((void *)name);
			break ;
		}
		ptr = ptr->next;
	}	
}

int	export_name(t_list **env, t_list **export, char *name)
{
	int	i;
	int	check;
	
	i = 0;
	check = 0;
	if (!(*env) || !(*export))
		return(1);
	if (name[0] == '=')
		return (2);
	while(name[i])
	{
		if (name[i] == '=')
			check = 1;
		i++;
	}
	if (check == 1)
	{
		if (is_in_list(export, ft_get_name(name)) == 1)
		{
			printf("THERE IS A DOUBLE\n");
			found_and_replace(export, name);
		}
		else
		{
			printf("else????????\n");
			ft_lstadd_back(export, ft_lstnew((void *)name));
		}
		// checker si il existe deja dans export, si oui, le free et le remplacer par le nouveau maillon
		// else le addback dans export;
		if (is_in_list(env, ft_get_name(name)) == 0)
		{
			printf("put in list env\n");
			ft_lstadd_back(env, ft_lstnew((void *)name));
		}
	}
	else if (is_in_list(export, ft_get_name(name)) == 0)
		ft_lstadd_back(export, ft_lstnew((void *)name));
	return (0);
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
