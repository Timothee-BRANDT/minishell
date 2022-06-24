/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:12:20 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/24 18:23:17 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_manage(void	*to_add)
{
	static t_list	*manage;

	ft_lstadd_back(&manage, ft_lstnew(to_add));
}

t_list	*get_in_list(char	*buffer, t_data	*data, t_list	*lst)
{
	while (ft_isspace(buffer[data->count]) == 1)
		data->count++;
	if (buffer[data->count] != ' ' || buffer[data->count] == '\0')
		lst = ft_list(lst, data);
	return (lst);
}

int	add_it(t_data	*data, int	i, int j)
{
	if (ft_check_token(data->buffer[i + 1]) == 0)
	{
		data->add_space2buffer[j] = data->buffer[i];
		data->add_space2buffer[j + 1] = ' ';
		data->add_space2buffer[j + 2] = data->buffer[i + 1];
		data->add_space2buffer[j + 3] = ' ';
		j += 4;
		i += 1;
	}
	return (j);
}

void	add_space(t_data	*data)
{
	int	len;

	len = get_len4addspace(data);
	data->i_space = 0;
	data->j_space = 0;
	data->add_space2buffer = malloc(sizeof(char) * len + 1);
	if (!data->add_space2buffer)
		return ;
	if (data->buffer && data->buffer[data->i_space])
	{
		while (data->i_space < len)
		{

			/*if (data->buffer[data->i_space] == '"' || data->buffer[data->i_space] == '\'')
				data->i_space = skip_it(data);*/

			if (ft_check_token(data->buffer[data->i_space + 1]) == 0 && data->buffer[data->i_space + 1] == data->buffer[data->i_space + 2])
			{
				data->add_space2buffer[data->j_space] = data->buffer[data->i_space + 2];
				data->add_space2buffer[data->j_space + 1] = ' ';
				data->add_space2buffer[data->j_space + 2] = data->buffer[data->i_space + 3];
				data->add_space2buffer[data->j_space + 3] = ' ';
				data->j_space += 4;
				data->i_space += 3;
			}

			else if (ft_check_token(data->buffer[data->i_space + 1]) == 0)
			{
				data->add_space2buffer[data->j_space] = data->buffer[data->i_space];
				data->add_space2buffer[data->j_space + 1] = ' ';
				data->add_space2buffer[data->j_space + 2] = data->buffer[data->i_space + 1];
				data->add_space2buffer[data->j_space + 3] = ' ';
				data->j_space += 3;
				data->i_space += 1;
			}

			else
				data->add_space2buffer[data->j_space] = data->buffer[data->i_space];
			data->j_space++;
			data->i_space++;
		}
		data->buffer = ft_calloc(1, ft_strlen(data->add_space2buffer + 1));
		data->buffer = ft_strncpy(data->buffer, data->add_space2buffer, ft_strlen(data->add_space2buffer) + 1);
	}
}

int	ft_check_token(char	c)
{
	char	*token;
	int		i;

	i = 0;
	token = "><|";
	while (token[i])
	{
		if (c == token[i])
			return (0);
		i++;
	}
	return (1);
}

int	get_len4addspace(t_data	*data)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (data->buffer && data->buffer[i])
	{
		while (ft_check_token(data->buffer[i]) == 1 && data->buffer[i] != '\0')
			i++;
		if (ft_check_token(data->buffer[i]) == 0 && data->buffer[i] != '\0')
		{
			if (data->buffer[i] == data->buffer[i + 1])
			{
				i += 2;
				res += 2;
			}
			else
			{
				i++;
				res += 2;
			}
		}
	}
	return (i + res);
}

int	skip_it(t_data	*data)
{
	char	tmp;

	tmp = data->buffer[data->i_space];
	data->i_space++;
	while (data->buffer[data->i_space] && data->buffer[data->i_space] != tmp)
	{
		data->add_space2buffer[data->j_space] = data->buffer[data->i_space];
		data->j_space++;
		data->i_space++;
	}
	if (data->buffer[data->i_space] == tmp)
	{
		data->add_space2buffer[data->j_space] = data->buffer[data->i_space];
		data->i_space+=1;
	}
	return (data->i_space);
}
