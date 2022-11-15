/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:34:37 by mmatthie          #+#    #+#             */
/*   Updated: 2022/11/15 16:18:33 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_word(char	*str, t_data *data, int count)
{
	int	i;
	int	j;

	i = 0;
	j = count;
	while ((str[j] && str) && (str[j] != '"'\
	&& str[j] != '\'') && (str[j] != ' ' && str[j] != '$'))
	{
		j++;
		i++;
	}
	data->first = ft_substr(str, count, i);
	if (str[j] != ' ' && str[j] && str)
		j = get_join(str, j, data);
	else
	{
		data->get_word = ft_strdup(data->first);
		free (data->first);
	}
	return (j);
}

static int	get_join_and_manage(char	*buffer, int i, t_data	*data)
{
	i = get_join(buffer, i, data);
	ft_manage(data->first);
	return (i);
}

static void	else_in_double_quotes(int j, t_data	*data)
{
	if (j > 0)
	{
		data->get_word = ft_strdup(data->first);
		free (data->first);
	}
	else
		data->get_word = ft_strdup(" ");
}

static int	increment_it(char	*buffer, t_data	*data)
{
	if (buffer[data->i_get] && data->token \
	&& buffer[data->i_get] == data->token)
	{
		data->i_get = last_token(data->i_get, data);
		return (-1);
	}
	while (buffer[data->i_get] && buffer[data->i_get] \
	!= data->token && buffer[data->i_get] != '$')
	{
		data->i_get++;
		data->j_get++;
	}	
	if ((buffer[data->i_get] && buffer[data->i_get] == '$') \
	&& (buffer[data->i_get + 1] && buffer[data->i_get + 1] == '"'))
	{
		data->j_get++;
		data->i_get++;
	}
	return (0);
}

int	get_double_quotes(char	*buffer, t_data	*data, int count)
{
	data->token = buffer[count];
	count++;
	data->i_get = count;
	if (increment_it(buffer, data) == -1)
		return (data->i_get);
	if (data->j_get > 0)
		data->first = ft_substr(buffer, count, data->j_get);
	if (buffer && buffer[data->i_get] == '"')
		data->i_get = last_token(data->i_get, data);
	if (buffer && buffer[data->i_get] && buffer[data->i_get] == '$')
		data->i_get = get_expend_with_token(buffer, data->i_get, count, data);
	else if (buffer && buffer[data->i_get] && buffer[data->i_get] != ' ')
		data->i_get = get_join_and_manage(buffer, data->i_get, data);
	else
		else_in_double_quotes(data->j_get, data);
	data->j_get = 0;
	return (data->i_get);
}
