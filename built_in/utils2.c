/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:57:36 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/21 17:26:0 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	char	*get_key;

	ptr = *list;
	while(ptr->next != NULL)
	{
		get_key = ft_get_key((char *)(ptr->next->content));
		if (ft_strcmp(get_key, name) == 0)
		{
			free(get_key);
			return (1);
		}
		ptr = ptr->next;
		free(get_key);
	}
	return (0);
}

void	found_and_replace(t_list **export, char *name)
{
	t_list	*ptr;
	t_list	*tmp;
	char	*get_key_export;
	char	*get_key_name;

	ptr = *export;
	while (ptr)
	{
		get_key_export = ft_get_key((char *)(ptr->next->content));
		get_key_name = ft_get_key(name);
		if (ft_strcmp(get_key_export, get_key_name) == 0)
		{
			free_two_string(get_key_export, get_key_name);
			tmp = ptr->next->next;
			free(ptr->next);
			ptr->next = ft_lstnew((void *)name);
			ptr->next->next = tmp;
			break ;
		}
		free_two_string(get_key_export, get_key_name);
		ptr = ptr->next;
	}	
}

void    found_and_add(t_list **export, char *name, t_data *data)
{
	t_list  *ptr; 
	t_list  *tmp;
	char	*string;
	char	*get_key_export;
	char	*get_key_name;
	
	ptr = *export;
	while (ptr)
	{
		get_key_export = ft_get_key((char *)(ptr->next->content));
		get_key_name = ft_get_key(name);
		if (ft_strcmp(get_key_export, get_key_name) == 0)
		{
			string = ft_strjoin_export(get_key_export, get_key_name);
			free_two_string(get_key_export, get_key_name);
			data->result = ft_strjoin(string, ft_get_value(name));
			tmp = ptr->next->next;
            free(ptr->next);
			ptr->next = ft_lstnew(data->result);
			ptr->next->next = tmp;
			break ;
		}
		free_two_string(get_key_export, get_key_name);
		ptr = ptr->next;
	}
}

char	*remove_plus(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		k;
	
	i =	0;
	j = 0;
	k = 0;
	res = malloc(sizeof(char) * ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '+')
			i++;
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}