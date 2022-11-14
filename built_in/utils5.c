/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:23:18 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/14 12:35:20 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_v2_export(char *key, t_data *data)
{
	t_list	*tmp;
	int		len;
	char	*value;

	tmp = data->export;
	len = ft_strlen(key);
	while (tmp)
	{
		if (!ft_strncmp_v2((char *)tmp->content, key, len))
		{
			value = ft_get_value((char *)tmp->content);
			return (value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	free_list(void *ptr)
{
	t_list	*list;

	list = ptr;
	free(list);
}

void	print_tab(char **tab, t_data *data)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		dprintf(data->tmp_out, "tab[%d]: %s\n", i, tab[i]);
		i++;
	}
}

void	free_2_tab(char **tab1, char **tab2, t_data *data)
{
	data->check_fd_out = 0;
	data->check_fd_in = 0;
	free_tab(tab1);
	free_tab(tab2);
}

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[i] : %s\n", tab[i]);
		i++;
	}
}
