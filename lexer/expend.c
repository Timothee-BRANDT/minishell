/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 02:46:39 by mmatthie          #+#    #+#             */
/*   Updated: 2022/10/27 16:42:48 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_expend(char	*str, int j, int count, t_data	*data)
{
	int	tmp;

	tmp = 0;
	if (str && str[j] && str[j] == '$')
	{
		while (str[j] == '$')
			j++;
		count = j;
		while ((str && str[j]) && (str[j] != '"' \
		&& str[j] != '\'') && (str[j] != ' ' && str[j] != '$') && str[j] != '?')
		{
			tmp++;
			j++;
		}
		count = make_expend(str, count, tmp, data);
		if (str[count] != ' ' && str[count])
		{
			data->first = ft_strdup(data->get_word);
			free_it(data->get_word);
			count = get_join(str, count, data);
		}
	}
	return (count);
}

int	first_expend(char	*str, int count, t_data	*data)
{
	int	j;

	j = count;
	if (str[j] == '$')
		count = get_expend_without_first(str, j, data);
	if (str[count] != ' ' && str[count])
	{
		if ((str[count] == ' ' || str[count] == '"'))
			count = get_join(str, count, data);
	}
	return (count);
}

int	get_expend_with_token(char	*str, int j, int count, t_data	*data)
{
	int	tmp;

	tmp = 0;
	if (str[j] == '$')
	{
		while (str[j] == '$')
			j++;
		count = j;
		while ((str[j] != data->token && str[j] != '$' \
		&& str[j] != '\'') && (str && str[j]) && str[j] != '?')
		{
			tmp++;
			j++;
		}
		if (str && str[j] && str[j] == data->token)
			j = last_token(j, data);
		count = make_expend(str, count, tmp, data);
		if (str[j] && str[j] != ' ')
		{
			data->first = ft_strdup(data->get_word);
			free_it (data->get_word);
			count = get_join(str, j, data);
		}
	}
	return (count);
}

int	make_expend(char	*str, int j, int content, t_data	*data)
{
	char	*expend;
	int		count;

	count = content + j;
	expend = ft_substr(str, j, content);
	data->expend = get_env(expend, data->export);
	expend_it(data, str, j);
	free_it(data->expend);
	free_it(expend);
	if (str && str[count] && (str[count] == '"' || (str[count] == '?' && str[count - 1] == '$')))
		return (count + 1);
	return (count);
}

void	little_one(t_data	*data)
{
	data->get_word = ft_calloc(1, 1);
	data->get_word[0] = '\0';
}