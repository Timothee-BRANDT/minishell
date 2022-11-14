/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:37:57 by mmatthie          #+#    #+#             */
/*   Updated: 2022/11/09 11:47:49 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_token(t_data	*data, char	*buffer, int count)
{
	data->token = buffer[count];
	count++;
	return (count);
}

int	last_token(int count, t_data	*data)
{
	data->token = 0;
	count++;
	return (count);
}

void	get_and_free(t_data	*data)
{
	data->get_word = ft_strdup(data->first);
	free_it(data->first);
}

int	reset_indicate(int count, t_data	*data)
{
	count += 1;
	data->indicate = 0;
	return (count);
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
		count = get_expend(buffer, tmp, tmp, data);
	return (count);
}
