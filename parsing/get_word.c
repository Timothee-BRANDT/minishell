/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:34:37 by mmatthie          #+#    #+#             */
/*   Updated: 2022/10/18 12:55:12 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_word(char	*str, t_data *data, int count)
{
	int	i;
	int	j;

	i = 0;
	j = count;
	while (str[j] != '"' && str[j] != '\'' && str[j] != '\0' && str[j] != ' ' && str[j] != '$')
	{
		j++;
		i++;
	}
	data->first = ft_substr(str, count, i);
	if (str[j] != ' ' && str[j])
		j = get_join(str, j, data);
	else
	{
		data->get_word = ft_strdup(data->first);
		free (data->first);
	}
	return (j);
}

int	get_simple_quotes(char	*buffer, int count, t_data *data)
{
	int	i;
	int	j;

	j = 0;
	data->token = buffer[count];
	i = count;
	while (buffer[++i] && buffer[i] != data->token)
		j++;
	if (buffer[i] && buffer[i] == data->token)
	{
		i++;
		data->token = 0;
	}
	count += 1;
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

int	get_double_quotes(char	*buffer, t_data	*data, int count)
{
	int	i;
	int	j;

	j = 0;
	data->token = buffer[count];
	count++;
	i = count;
	while (buffer[i] && buffer[i] != data->token && buffer[i] != '$')
	{
		i++;
		j++;
	}
	if (j > 0)
		data->first = ft_substr(buffer, count, j);
	if (buffer[i] == '"')
	{
		data->token = 0;
		++i;
	}
	if (buffer[i] == '$')
		i = get_expend(buffer, i , count, data);
	else if (buffer[i] && buffer[i] != ' ')
		i = get_join(buffer, i, data);
	else
	{
		if (data->first && data->first[0])
		{
			data->get_word = ft_strdup(data->first);
			free (data->first);
		}
	}
	return (i);
}

int	get_without_quotes(char	*buffer, t_data	*data, int count)
{
	int	tmp;
	int	j;

	j = 0;
	tmp = count;
	while (buffer[tmp] != '"' && buffer[tmp] != '\'' \
	&& buffer[tmp] && buffer[tmp] != ' ' && buffer[tmp] != '$')
	{
		j++;
		tmp++;
	}
	data->second = ft_substr(buffer, count, j);
	data->join = ft_join_free_ss(data->first, data->second);
	if (!data->join)
	{
		ft_putstr_fd("error in join\n", 2);
		exit(EXIT_FAILURE);
	}
	data->first = ft_strdup(data->get_word);
	count = tmp;
	if (buffer[tmp] && buffer[tmp] == '$')
		count = get_expend(buffer, tmp , tmp, data);
	return (count);
}
