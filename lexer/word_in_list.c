/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_in_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:08:29 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/03 17:27:38 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_list(t_list	*lst, t_data	*data)
{
	ft_lstadd_back(&lst, ft_lstnew(data->get_word));
	return (lst);
}

int	get_second_without_token(char	*str, int count, t_data	*data)
{
	int	i;
	int	tmp;

	tmp = 0;
	i = count;
	while (str[i] && (str[i] != '\'' && str[i] != ' ') && (str[i] != '"' && str[i] != '$'))
	{
		i++;
		tmp++;
	}
	if (tmp > 0)
	{
		data->second = ft_substr(str, count, tmp);
		data->join = ft_join_free_ss(data->first, data->second);
		data->first = ft_strdup(data->join);
		free(data->join);
	}
	if (str[i] && str[i] == data->token)
		i = last_token(i , data);
	if (str[i] && str[i] == '$')
		i = get_expend(str, i, count, data);
	else if (!str[i] || str[i] == ' ')
	{
		data->get_word = ft_strdup(data->first);
		free(data->first);
	}
	if (str[i] && str[i] != ' ')
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

void	check_token(char	*buffer, int count, t_data	*data)
{
	if (!data->token)
	{
		if (buffer[count] && (buffer[count] == '"' || buffer[count] == '\''))
			data->token = buffer[count];
		if (buffer[count] == data->token || buffer[count] == buffer[count + 1] || buffer[count] == buffer[count - 1])
			count += 1;
	}
}

int	get_second_simple(char	*str, int count, t_data	*data)
{
	int	i;
	int tmp;

	if (data->indicate != 0)
		count = reset_indicate(count, data);
	i = count;
	tmp = 0;
	while (str[++i] && str[i] != data->token)
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

int	get_second_double(char	*str, int count, t_data	*data)
{
	int	i;
	int	tmp;

	tmp = 0;
	if (data->indicate == 1)
		reset_indicate(count, data);
	i = count;
	while (str && str[i] && str[i] != data->token && str[i] != '$')
	{
		++tmp;
		++i;
	}
	if (tmp > 0)
	{
		data->second = ft_substr(str, count, tmp);
		data->join = ft_join_free_ss(data->first, data->second);
	}
	else
	{
		data->get_word = ft_strdup(data->first);
		ft_manage(data->first);
	}
	i = get_next(str, i, data, tmp);
	return (i);
}

int	get_next(char	*str, int i, t_data	*data, int tmp)
{
	if (str && str[i] == data->token)
		i = last_token(i, data);
	if (tmp > 0)
	{
		data->first = ft_strdup(data->join);
		free_it(data->join);
	}
	if (str[i] == '$')
		i = get_expend(str, i , tmp, data);
	else if (str && str[i] && str[i] != ' ')
		i = get_join(str, i, data);
	else
	{
		if (tmp > 0)
		{
			data->get_word = ft_strdup(data->first);
			free_it(data->first);
		}
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
	// printf("\n\n\nlst : %p\n\n\n", lst);
	return (lst);
}
