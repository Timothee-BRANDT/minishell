/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 09:22:04 by mmatthie          #+#    #+#             */
/*   Updated: 2022/11/13 13:33:49 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_token(char	*buffer, int count, t_data	*data)
{
	if (!data->token)
	{
		if (buffer[count] && (buffer[count] == '"' || buffer[count] == '\''))
			data->token = buffer[count];
		if (buffer[count] == data->token || buffer[count] \
		== buffer[count + 1] || buffer[count] == buffer[count - 1])
			count += 1;
	}
	else
		data->indicate = 1;
}

int	get_expend_without_first(char	*str, int count, t_data	*data)
{
	int	tmp;
	int	j;

	j = 0;
	tmp = 0;
	if (str && str[count])
	{
		while (str[count] == '$' && str[count + 1])
			count++;
		j = count;
		while ((str && str[count]) && (str[count] != '"' && \
		str[count] != '\'') && (str[count] != '$' \
		&& str[count] != ' ') && str[count] != '?')
		{
			tmp++;
			count++;
		}
		count = make_expend(str, j, tmp, data);
		if (str[count] != ' ' && str[count])
			count = get_join_and_free(str, count, data);
	}
	return (count);
}

void	little_one(t_data	*data)
{
	data->get_word = ft_strdup("\0");
}

int	get_simple_quotes(char	*buffer, int count, t_data *data)
{
	int	i;
	int	j;

	j = 0;
	data->token = buffer[count];
	count += 1;
	i = count;
	while (buffer[i] && buffer[i] != data->token)
	{
		i++;
		j++;
	}
	if (buffer[i] && data->token && buffer[i] == data->token)
		i = last_token(i, data);
	data->first = ft_substr(buffer, count, j);
	if (buffer[i] && buffer[i] != ' ')
		i = get_join(buffer, i, data);
	else
	{
		data->get_word = ft_strdup(data->first);
		free(data->first);
	}
	return (i);
}
