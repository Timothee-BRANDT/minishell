/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:55:41 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/14 12:19:49 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd_export(t_data *data)
{
	t_list	*ptr;
	char	cwd[256];
	char	*list_key;

	ptr = data->export;
	getcwd(cwd, sizeof(cwd));
	while (ptr)
	{
		list_key = ft_get_key((char *)ptr->content);
		if (!ft_strcmp("PWD", list_key))
		{
			free(list_key);
			free(ptr->content);
			ptr->content = ft_strjoin("PWD=", cwd);
			break ;
		}
		free(list_key);
		ptr = ptr->next;
	}
}

void	change_pwd_env(t_data *data)
{
	t_list	*ptr;
	char	cwd[256];
	char	*list_key;

	ptr = data->env;
	getcwd(cwd, sizeof(cwd));
	while (ptr)
	{
		list_key = ft_get_key((char *)ptr->content);
		if (!ft_strcmp("PWD", list_key))
		{
			free(list_key);
			free(ptr->content);
			ptr->content = ft_strjoin("PWD=", cwd);
			break ;
		}
		free(list_key);
		ptr = ptr->next;
	}
}

void	change_oldpwd_env(t_data *data, char *pwd)
{
	t_list	*ptr;
	char	*list_key;

	ptr = data->env;
	while (ptr)
	{
		list_key = ft_get_key((char *)ptr->content);
		if (!ft_strcmp("OLDPWD", list_key))
		{
			free(list_key);
			free(ptr->content);
			ptr->content = ft_strjoin("OLDPWD=", pwd);
			break ;
		}
		free(list_key);
		ptr = ptr->next;
	}
}

void	change_oldpwd_export(t_data *data, char *pwd)
{
	t_list	*ptr;
	char	*list_key;

	ptr = data->export;
	while (ptr)
	{
		list_key = ft_get_key((char *)ptr->content);
		if (!ft_strcmp("OLDPWD", list_key))
		{
			free(list_key);
			free(ptr->content);
			ptr->content = ft_strjoin("OLDPWD=", pwd);
			break ;
		}
		free(list_key);
		ptr = ptr->next;
	}
}
