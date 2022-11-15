/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:12:20 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/15 12:02:18 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_list(t_list	*lst, t_data	*data)
{
	ft_lstadd_back(&lst, ft_lstnew(data->get_word));
	return (lst);
}

static void	do_else_in_get_second_double(t_data	*data)
{
	data->get_word = ft_strdup(data->first);
	ft_manage(data->first);
}

int	get_second_double(char	*str, int count, t_data	*data)
{
	int	i;
	int	tmp;

	tmp = 0;
	if (data->indicate != 1)
		count = reset_indicate(count, data);
	i = count;
	while (str && str[i] && str[i] != data->token && str[i] != '$')
	{
		i++;
		tmp++;
	}
	if (str && data->token && str[i] == data->token)
		i = last_token(i, data);
	if (tmp > 0)
	{
		data->second = ft_substr(str, count, tmp);
		data->join = ft_join_free_ss(data->first, data->second);
	}
	else
		do_else_in_get_second_double(data);
	i = get_next(str, i, data, tmp);
	return (i);
}

int	get_next(char	*str, int i, t_data	*data, int tmp)
{
	if (str && data->token && str[i] == data->token)
		i = last_token(i, data);
	if (tmp > 0)
	{
		data->first = ft_strdup(data->join);
		free_it(data->join);
	}
	if (str && str[i] == '$')
		i = get_expend(str, i, tmp, data);
	else if (str && str[i] && str[i] != ' ')
		i = get_join(str, i, data);
	else
	{
		if (tmp > 0)
		{
			data->get_word = ft_strdup(data->first);
			free_it (data->first);
		}
	}
	return (i);
}
