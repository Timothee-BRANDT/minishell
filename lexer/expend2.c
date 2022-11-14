/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 02:54:11 by mmatthie          #+#    #+#             */
/*   Updated: 2022/11/14 16:17:35 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(char *key, t_list *export)
{
	t_list	*tmp;
	int		len;
	char	*tab;

	tab = NULL;
	tmp = export;
	len = ft_strlen(key);
	if (key && key[0])
	{
		if (!ft_strncmp((char *)tmp->content, key, len))
		{
			tab = ft_get_value((char *)tmp->content);
			return (tab);
		}
		while (tmp->next)
		{
			if (!ft_strncmp((char *)tmp->next->content, key, len))
			{
				tab = ft_get_value((char *)tmp->next->content);
				return (tab);
			}
			tmp = tmp->next;
		}
	}
	return (NULL);
}

static void	do_else_if(t_data	*data)
{
	if (data->expend == NULL)
		get_and_free(data);
	else
	{
		ft_manage(data->get_word);
		data->get_word = ft_join_free_s1(data->first, data->expend);
	}
}

void	expend_it(t_data	*data, char	*str, int j)
{
	int	tmp;

	tmp = j - 2;
	if (str && str[tmp])
		while ((str && str[tmp]) && (str[tmp] \
		== '"' || str[tmp] == '$') && str[tmp] != ' ')
			tmp--;
	if (str && str[j] && str[j] == '?')
	{
		if (tmp > -1 && (str[tmp] && str[tmp] != ' ') \
		&& (data->token == 0 || data->token == '"'))
			data->get_word = \
			ft_join_free_s1(data->first, ft_itoa_v2(g_glo.g_signum));
		else
			data->get_word = ft_itoa_v2(g_glo.g_signum);
		j++;
	}
	else if (tmp > -1 && (str[tmp] && str[tmp] != ' ') \
	&& (data->token == 0 || data->token == '"'))
		do_else_if(data);
	else
		do_else(data);
}

void	do_else(t_data	*data)
{
	if (data->expend == NULL)
		little_one(data);
	else
		data->get_word = ft_strdup(data->expend);
}

int	get_join_and_free(char	*str, int count, t_data	*data)
{
	data->first = ft_strdup(data->get_word);
	free_it(data->get_word);
	count = get_join(str, count, data);
	return (count);
}
