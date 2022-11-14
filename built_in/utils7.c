/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:07:48 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/14 16:26:51 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_export_main(char **tab, t_data *data)
{
	t_list	*list;

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
		if (data->fd_out)
		{
			dup2(data->fd_out, 1);
			close(data->fd_out);
		}
		start_echo(tab);
		return (0);
	}
	return (1);
}

int	is_env_main(char **tab, t_data *data)
{
	if (tab[0] && !ft_strcmp(tab[0], "env") && !data->check_pipe)
	{
		if (tab[1] && !ft_strcmp(tab[1], ">"))
			return (1);
		ft_print_env(data->env);
		return (0);
	}
	return (1);
}

int	is_unset_main(char **tab, t_data *data)
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

int	is_cd_main(char **tab, t_data *data)
{
	char	*pwd;

	if (tab[0] && !ft_strcmp(tab[0], "cd") && !data->check_pipe)
	{
		pwd = get_env_v2_export("PWD", data);
		if (tab[1])
		{
			if (error_open(tab, pwd))
			{
				g_glo.g_signum = 1;
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
