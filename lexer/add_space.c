/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 02:44:29 by mmatthie          #+#    #+#             */
/*   Updated: 2022/11/01 18:35:19 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	skip_quotes(char	*buffer, int i)
{
	char	tmp;

	tmp = buffer[i];
	i++;
	while (buffer[i] != tmp && buffer[i])
		i++;
	return (i + 1);
}

int	ft_check_token(char c)
{
	char	*token;
	int		i;

	i = 0;
	token = "><|";
	while (token && token[i])
	{
		if (c == token[i])
			return (0);
		i++;
	}
	return (1);
}

static int	check_len4add_space(char	*buffer, t_data	*data)
{
	int	i;
	int	res;

	res = 0;
	i = 0;
	(void) data;
	if (buffer && buffer[i])
	{
		while (buffer && buffer[i])
		{
			while ((ft_check_token(buffer[i]) == 1) \
			&& buffer[i] != '\'' && buffer[i] != '"' && buffer[i])
				i++;
			if (buffer[i] == '\'' || buffer[i] == '"')
				i = skip_quotes(buffer, i);
			if (ft_check_token(buffer[i]) == 0)
			{
				while (ft_check_token(buffer[i]) == 0)
					i++;
				res += 2;
			}
		}
	}
	return (i + res);
}

static char	*ft_space_routine(char	*buffer, t_data	*data, char	*str)
{
	if (buffer && buffer[data->i_space])
	{
		while (buffer && buffer[data->i_space])
		{
			while ((ft_check_token(buffer[data->i_space]) == 1) \
			&& buffer[data->i_space] != '\'' && \
			buffer[data->i_space] != '"' && buffer[data->i_space])
			{
				str[data->j_space] = buffer[data->i_space];
				data->i_space++;
				data->j_space++;
			}
			if (buffer[data->i_space] == '"' || buffer[data->i_space] == '\'')
				data->i_space = fill_quotes(str, buffer, data);
			if (ft_check_token(buffer[data->i_space]) == 0)
				set_redir(data, str, buffer);
		}
	}
	return (str);
}

char	*ft_add_space(char	*buffer, t_data	*data)
{
	char	*str;

	data->space_len = check_len4add_space(buffer, data);
	str = malloc(sizeof(char) * data->space_len + 1);
	if (!str)
		return (NULL);
	if (buffer && buffer[data->i_space])
		str = ft_space_routine(buffer, data, str);
	str[data->space_len] = '\0';
	free (buffer);
	return (str);
}
