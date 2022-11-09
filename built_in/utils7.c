/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:07:48 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/09 17:05:19 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_pipe(char **tab, t_data *data)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (!ft_strcmp(tab[i], "|"))
		{
			data->check_pipe = 1;
			return (1);
		}
		i++;
	}
	data->check_pipe = 0;
	return (0);
}

int is_export(char **tab, t_data *data)
{
    t_list *list;

    if (tab[0] && !ft_strcmp(tab[0], "export"))
    {
		if (ft_strlen2d(tab) > 1 && !data->check_pipe)
    	{
	    	list = dpt_to_lst_export(tab);
		    export_name(&list, data);
		    ft_lstclear(&list, free);
            return (1);
    	}
    }
	return (0);
}

int is_unset(char **tab, t_data *data)
{
    t_list *list;
    
    if (tab[0] && !ft_strcmp(tab[0], "unset"))
	{
		if (!tab[1])
			return (1);
		if (!data->check_pipe)
		{
			list = dpt_to_lst_env(tab);
			unset_name_env(&data->env, &list);
			unset_name_export(&data->export, &list);
			ft_lstclear(&list, free);
			return (1);
		}
	}
    return (0);
}

void	change_oldpwd_export(char *pwd, t_data *data)
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
			ptr->next = ft_lstnew(ft_strjoin("OLDPWD:", pwd));
			ptr->next->next = tmp;
			break ;
		}
		ptr = ptr->next;
	}
}

void	chdir_home(t_data *data)
{
	char	*home;

	home = get_env_v2("HOME", data->env);
	chdir(home);
	free(home);
}

int is_cd(char **tab, t_data *data)
{
	char	*pwd;
	char	*oldpwd;

	if (tab[0] && !ft_strcmp(tab[0], "cd"))
	{
		pwd = get_env_v2("PWD", data->env);
		oldpwd = get_env_v2("OLDPWD", data->env);
		printf("actual pwd: %s\n", pwd);
		printf("actual oldpwd: %s\n", oldpwd);
		if (tab[1])
			chdir(tab[1]);
		else
			chdir_home(data);
		// change_oldpwd_export(pwd, data);
		// change_oldpwd_env(pwd, data);
		// apres le cd -> oldpwd devient pwd;
		// et pwd devient le getpwd du dossier actuel;
		free(pwd);
		free(oldpwd);
		return (1);
	}
	return (0);
}