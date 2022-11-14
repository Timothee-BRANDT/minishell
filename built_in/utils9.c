/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils9.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:35:29 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/14 12:11:51 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*dpt_to_lst_export(char **env)
{
	t_list	*list;
	int		i;

	i = 2;
	if (!env[0])
	{
		list = ft_lstnew("");
		return (list);
	}
	else
		list = ft_lstnew(ft_strdup(env[1]));
	while (env[i])
	{
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(env[i])));
		i++;
	}
	return (list);
}

t_list	*dpt_to_lst_env(char **env)
{
	t_list	*list;
	int		i;

	i = 1;
	if (!env[0])
	{
		list = ft_lstnew("");
		return (list);
	}
	else
		list = ft_lstnew(ft_strdup(env[0]));
	while (env[i])
	{
		ft_lstadd_back(&list, ft_lstnew(ft_strdup(env[i])));
		i++;
	}
	return (list);
}

int	on_error(char *str, int code)
{
	write(1, str, ft_strlen(str));
	return (code);
}

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
