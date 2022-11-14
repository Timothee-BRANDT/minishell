/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:53:37 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/14 12:22:30 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_export_child(char **tab, t_data *data)
{
	t_list	*list;

	if (tab[0] && !ft_strcmp(tab[0], "export"))
	{
		if (!tab[1])
		{
			ft_print_env(data->export);
			return (0);
		}
		if (ft_strlen2d(tab) > 1)
		{
			list = dpt_to_lst_export(tab);
			export_name(&list, data);
			ft_lstclear(&list, free);
			return (0);
		}
	}
	return (1);
}

int	is_echo_child(char **tab, t_data *data)
{
	(void)data;
	if (tab[0] && !ft_strcmp(tab[0], "echo"))
	{
		start_echo(tab);
		return (0);
	}
	return (1);
}

int	is_env_child(char **tab, t_data *data)
{
	(void)data;
	if (tab[0] && !ft_strcmp(tab[0], "env"))
	{
		ft_print_env(data->env);
		return (0);
	}
	return (1);
}

int	is_unset_child(char **tab, t_data *data)
{
	t_list	*list;

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

int	is_cd_child(char **tab, t_data *data)
{
	char	*pwd;

	if (tab[0] && !ft_strcmp(tab[0], "cd"))
	{
		pwd = get_env_v2_export("PWD", data);
		if (tab[1])
		{
			if (open(tab[1], O_DIRECTORY) == -1)
			{
				if (error_open(tab, pwd))
					return (0);
			}
			chdir(tab[1]);
			change_pwd(data, pwd);
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
