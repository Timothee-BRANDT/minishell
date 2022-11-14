/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_in_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:08:29 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/09 17:45:24 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	do_if_in_without(char	*str, int count, int tmp, t_data	*data)
{
	data->second = ft_substr(str, count, tmp);
	data->join = ft_join_free_ss(data->first, data->second);
	data->first = ft_strdup(data->join);
	free(data->join);
}

int	get_second_without_token(char	*str, int count, t_data	*data)
{
	int	i;
	int	tmp;

	tmp = 0;
	if (data->indicate == 1)
		count = reset_indicate(count, data);
	i = count;
	while (str[i] && (str[i] != '\'' && \
	str[i] != ' ') && (str[i] != '"' && str[i] != '$'))
	{
		i++;
		tmp++;
	}
	if (tmp > 0)
		do_if_in_without(str, count, tmp, data);
	if (str[i] && str[i] == '$')
		i = get_expend(str, i, count, data);
	else if (!str[i] || str[i] == ' ')
	{
		data->get_word = ft_strdup(data->first);
		free(data->first);
	}
	else
		return (get_join(str, i, data));
	return (i);
}

int	get_second_with_token(char	*str, int count, t_data	*data)
{
	if (data->token == '"')
		count = get_second_double(str, count, data);
	else
		count = get_second_simple(str, count, data);
	return (count);
}

int	get_second_simple(char	*str, int count, t_data	*data)
{
	int	i;
	int	tmp;

	i = count;
	tmp = 0;
	while (str && str[++i] && str[i] != data->token)
		tmp++;
	if (tmp > 0)
	{
		data->second = ft_substr(str, count + 1, tmp);
		data->join = ft_join_free_ss(data->first, data->second);
		data->first = ft_strdup(data->join);
		free_it(data->join);
	}
	if (str[i] == data->token)
		i = last_token(i, data);
	if (str[i] && str[i] != ' ')
		i = get_join(str, i, data);
	else
	{
		data->get_word = ft_strdup(data->first);
		free_it(data->first);
	}
	return (i);
}

t_list	*get_word_in_list(char	*buffer, t_data	*data)
{
	t_list	*lst;

	lst = NULL;
	data->count = 0;
	if (buffer && buffer[0])
	{
		while (data->count < (int)ft_strlen(buffer))
		{
			data->get_word = NULL;
			while (buffer[data->count] && ft_isspace(buffer[data->count]))
				data->count++;
			if (buffer[data->count] == '"')
				data->count = get_double_quotes(buffer, data, data->count);
			else if (buffer[data->count] == '\'')
				data->count = get_simple_quotes(buffer, data->count, data);
			else if (buffer[data->count] == '$')
				data->count = first_expend(buffer, data->count, data);
			else
				data->count = get_word(buffer, data, data->count);
			if (buffer[data->count] == ' ' || buffer[data->count] == '\0')
				lst = get_in_list(buffer, data, lst);
		}
	}
	return (lst);
}
