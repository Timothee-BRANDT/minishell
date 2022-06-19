/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 14:31:02 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/15 18:00:44by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*env_to_list(char **env)
{
	t_list *list;
	int		i;

	i = 1;
	if (!env[0])
	{
		list = ft_lstnew("");
		return (list);
	}
	else
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
		if (ft_strcmp(ft_get_key((char *)(ptr->next->content)), name) == 0)
			return (1);
		ptr = ptr->next;
	}
	return (0);
}

void	found_and_replace(t_list **export, char *name)
{
	t_list	*ptr;
	t_list	*tmp;

	ptr = *export;
	while (ptr)
	{
		if (ft_strcmp(ft_get_key((char *)(ptr->next->content)), ft_get_key(name)) == 0)
		{
			tmp = ptr->next->next;
			free(ptr->next);
			ptr->next = ft_lstnew((void *)name);
			ptr->next->next = tmp;
			break ;
		}
		ptr = ptr->next;
	}	
}

void    found_and_add(t_list **export, char *name)
{
        t_list  *ptr;
        t_list  *tmp;
		char	*string;
		char	*res = NULL;

        ptr = *export;
        while (ptr)
        {
                if (ft_strcmp(ft_get_key((char *)(ptr->next->content)), ft_get_key(name)) == 0)
                {
						string = ft_strjoin_export(ft_get_key((char *)(ptr->next->content)), ft_get_value((char *)(ptr->next->content)));
						res = ft_strjoin(string, ft_get_value(name));
                        tmp = ptr->next->next;
                        free(ptr->next);
                        ptr->next = ft_lstnew(res);
                        ptr->next->next = tmp;
                        break ;
                }
                ptr = ptr->next;
        }
}

int	export_name(t_list **env, t_list **export, t_list **cmd, int code)
{
	int	i;
	int	check;
	int plus;
	char *str;
	
	i = -1;
	
	check = 0;
	plus = 0;
	if (code == 0)
		*cmd = (*cmd)->next;	
	str = ((char *)(*cmd)->content);
	if (is_token(str))
		return (2);
	if (ft_strcmp(str, "=") == 0)
		return (3);
	while (str[++i])
	{
		if (str[i] == '=')
		{
			check = 1;
			if (str[i - 1] == '+')
				plus = 1;
		}
	}
	if (check == 1)
	{
		if (is_in_list(export, ft_get_key(str)) == 1)
		{
			if (plus == 0)
				found_and_replace(export, str);
			else
			{
				check = 0;
				found_and_add(export, str);
				if (is_in_list(env, ft_get_key(str)) == 1)
					found_and_add(env, str);
			}
		}
		else
			ft_lstadd_back(export, ft_lstnew(remove_plus(str)));
		if (is_in_list(env, ft_get_key(str)) == 1 && check == 1)
				found_and_replace(env, str);
		if (is_in_list(env, ft_get_key(str)) == 0)
			ft_lstadd_back(env, ft_lstnew(remove_plus(str)));
	}
	else if (is_in_list(export, ft_get_key(str)) == 0)
		ft_lstadd_back(export, ft_lstnew(remove_plus(str)));
	if ((*cmd)->next != NULL && !is_token((char *)(*cmd)->next->content))
		return (export_name(env, export, &(*cmd)->next, 1));
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
