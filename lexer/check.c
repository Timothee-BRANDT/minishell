/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:34:37 by mmatthie          #+#    #+#             */
/*   Updated: 2022/06/23 10:08:11 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_word(char	*str, t_data *data, int count)
{
	int	i;
	int	j;

	i = 0;
	j = count;
	while (str[j] != '"' && str[j] != '\'' && str[j] != '\0' && str[j] != ' ')
	{
		j++;
		i++;
	}
	data->first = ft_calloc(1, i + 1);
	data->first = ft_strncpy(data->first, &str[count], i);
	if (str[j] == '"' || str[j] == '\'')
		count = get_join(str, count, j, data);
	else
	{
		data->get_word = ft_calloc(1, ft_strlen(data->first) + 1);
		data->get_word = ft_strncpy \
		(data->get_word, data->first, ft_strlen(data->first));
		ft_manage(data->get_word);
		count = j;
		free (data->first);
	}
	return (count);
}

int	get_second_word(char	*buffer, int count, t_data	*data)
{
	int	i;
	int	j;

	j = 0;
	if (buffer[count] == '"' || buffer[count] == '\'')
	{
		data->token = buffer[count];
		i = count;
		count++;
	}
	else
		return (count = get_without_quotes(buffer, data, count));
	count = make_second(buffer, data, count);
	return (count + 1);
}

int	get_without_quotes(char	*buffer, t_data	*data, int count)
{
	int	tmp;
	int	j;

	j = 0;
	tmp = count;
	while (buffer[tmp] != '"' && buffer[tmp] != '\'' \
	&& buffer[tmp] != '\0' && buffer[tmp] != ' ')
	{
		j++;
		tmp++;
	}
	data->second = ft_calloc(1, j + 1);
	data->second = ft_strncpy(data->second, &buffer[count], j);
	data->join = ft_join_free_ss(data->first, data->second);
	if (!data->join)
	{
		ft_putstr_fd("error in join\n", 2);
		exit(EXIT_FAILURE);
	}
	data->first = ft_calloc(1, ft_strlen(data->join) + 1);
	data->first = ft_strncpy(data->first, data->join, ft_strlen(data->join));
	ft_manage(data->first);
	ft_manage(data->join);
	count = tmp;
	return (count);
}

int	get_join(char	*str, int count, int j, t_data	*data)
{
	count = get_second_word(str, j, data);
	data->get_word = ft_calloc(1, ft_strlen(data->join) + 1);
	data->get_word = ft_strncpy \
	(data->get_word, data->join, ft_strlen(data->join));
	ft_manage(data->get_word);
	while (str[count] != ' ' && str[count])
	{
		count = get_second_word(str, count, data);
		data->get_word = ft_calloc(1, ft_strlen(data->join) + 1);
		data->get_word = ft_strncpy \
		(data->get_word, data->join, ft_strlen(data->join));
		data->first = ft_calloc(1, ft_strlen(data->join) + 1);
		data->first = ft_strncpy \
		(data->first, data->join, ft_strlen(data->join));
		ft_manage(data->get_word);
	}
	free(data->first);
	return (count);
}

char	*ft_join_free_ss(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (!s1)
	{
		s1 = ft_calloc(1, 1);
		if (!s1)
			return (NULL);
	}
	if (!s2)
		return (NULL);
	join = malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!join)
		return (NULL);
	i = -1;
	while (s1[++i])
		join[i] = s1[i];
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = 0;
	free(s1);
	free(s2);
	return (join);
}
