/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:07:48 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/12 17:20:39 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_pipe(char **tab, t_data *data)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		if (tab[i] && !ft_strcmp(tab[i], "|"))
		{
			data->check_pipe = 1;
			return (1);
		}
		i++;
	}
	data->check_pipe = 0;
	return (0);
}

int is_export_main(char **tab, t_data *data)
{
    t_list *list;

    if (tab[0] && !ft_strcmp(tab[0], "export") && !data->check_pipe)
    {
		if (tab[1] && !ft_strcmp(tab[1], ">"))
			return (1);
		if (ft_strlen2d(tab) > 1 && !data->check_pipe)
    	{
	    	list = dpt_to_lst_export(tab);
		    export_name(&list, data);
		    ft_lstclear(&list, free);
            return (0);
    	}
    }
	return (1);
}

int	is_echo_main(char **tab, t_data *data)
{
	if (tab[0] && !ft_strcmp(tab[0], "echo") && !data->check_pipe)
    {
        start_echo(tab);
        return (0);
    }
	return (1);
}

int	is_env_main(char **tab, t_data *data)
{
	if (tab[0] && !ft_strcmp(tab[0], "env") && !data->check_pipe)	
	{
		ft_print_env(data->env);
		return (0);
	}
	return (1);
}

int is_unset_main(char **tab, t_data *data)
{
    t_list *list;
    
    if (tab[0] && !ft_strcmp(tab[0], "unset"))
	{
		if (!tab[1])
			return (0);
		if (!data->check_pipe)
		{
			list = dpt_to_lst_env(tab);
			unset_name_env(&data->env, &list);
			unset_name_export(&data->export, &list);
			ft_lstclear(&list, free);
			return (0);
		}
	}
    return (1);
}

void	change_pwd_export(t_data *data)
{
	t_list	*ptr;
	char	cwd[256];
	t_list	*tmp;
	char	*list_key;
	
	ptr = data->export;
	getcwd(cwd, sizeof(cwd));
	while (ptr)
	{
		list_key = ft_get_key((char *)ptr->next->content);
		if (!ft_strcmp("PWD", list_key))
		{
			free(list_key);
			tmp = ptr->next->next;
			free(ptr->next->content);
			free(ptr->next);
			ptr->next = ft_lstnew(ft_strjoin("PWD=", cwd));
			ptr->next->next = tmp;
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
	t_list	*tmp;
	char	*list_key;
	
	ptr = data->env;
	getcwd(cwd, sizeof(cwd));
	while (ptr)
	{
		list_key = ft_get_key((char *)ptr->next->content);
		if (!ft_strcmp("PWD", list_key))
		{
			free(list_key);
			tmp = ptr->next->next;
			free(ptr->next->content);
			free(ptr->next);
			ptr->next = ft_lstnew(ft_strjoin("PWD=", cwd));
			ptr->next->next = tmp;
			break ;
		}
		free(list_key);
		ptr = ptr->next;
	}
}

void	change_oldpwd_env(t_data *data, char *pwd)
{
	t_list	*ptr;
	t_list	*tmp;
	char	*list_key;
	
	ptr = data->env;
	while (ptr)
	{
		list_key = ft_get_key((char *)ptr->next->content);
		if (!ft_strcmp("OLDPWD", list_key))
		{
			free(list_key);
			tmp = ptr->next->next;
			free(ptr->next->content);
			free(ptr->next);
			ptr->next = ft_lstnew(ft_strjoin("OLDPWD=", pwd));
			ptr->next->next = tmp;
			break ;
		}
		free(list_key);
		ptr = ptr->next;
	}
}

void	change_oldpwd_export(t_data *data, char *pwd)
{
	t_list	*ptr;
	t_list	*tmp;
	char	*list_key;
	
	ptr = data->export;
	while (ptr)
	{
		list_key = ft_get_key((char *)ptr->next->content);
		if (!ft_strcmp("OLDPWD", list_key))
		{
			free(list_key);
			tmp = ptr->next->next;
			free(ptr->next->content);
			free(ptr->next);
			ptr->next = ft_lstnew(ft_strjoin("OLDPWD=", pwd));
			ptr->next->next = tmp;
			break ;
		}
		free(list_key);
		ptr = ptr->next;
	}
}

int	chdir_home(t_data *data)
{
	char	*home;

	home = get_env_v2_export("HOME", data);
	if (!home)
	{
		printf("Bibishell: HOME not set.\n");
		free(home);
		return (1);
	}
	chdir(home);
	free(home);
	return (0);
}

int is_cd_main(char **tab, t_data *data)
{
	char	*pwd;

	if (tab[0] && !ft_strcmp(tab[0], "cd") && !data->check_pipe)
	{
		pwd = get_env_v2_export("PWD", data);
		if (tab[1])
		{
			chdir(tab[1]);
			change_pwd_export(data);
			change_pwd_env(data);
			change_oldpwd_export(data, pwd);
			change_oldpwd_env(data, pwd);
		}
		else if (chdir_home(data))
		{
			free(pwd);
			return (0);
		}
		free(pwd);
		return (0);
	}
	return (1);
}