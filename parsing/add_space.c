/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 11:17:02 by mmatthie          #+#    #+#             */
/*   Updated: 2022/06/27 11:16:08 by mmatthie         ###   ########.fr       */
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
	if (buffer[i] == tmp)
		i++;
	return (i);
}

static int	ft_check_token(char c, char d)
{
	char	*token;
	int		i;

	i = 0;
	token = "><|";
	while (token && token[i])
	{
		if (c == token[i])
		{
			if (c == d)
				return (2);
			else
				return (0);
		}
		i++;
	}
	return (1);
}

static int	check_len4add_space(char	*buffer, t_data	*data)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	(void) data;
	if (buffer && buffer[i])
	{
		while (buffer[i + 1])
		{
			while ((ft_check_token(buffer[i], buffer[i + 1]) == 1) \
			&& buffer[i] != '\'' && buffer[i] != '"' && buffer[i])
				i++;
			if (buffer[i] == '\'' || buffer[i] == '"')
				i = skip_quotes(buffer, i);
			if (ft_check_token(buffer[i], buffer[i + 1]) == 2)
			{
				res += 2;
				i += 2;
			}
			else if (ft_check_token(buffer[i], buffer[i + 1]) == 0)
			{
				res += 2;
				i++;
			}
		}
	}
	return (i + res);
}

char	*ft_add_space(char	*buffer, t_data	*data)
{
	int		len;
	int		i;
	int		j;
	char	*str;

	len = check_len4add_space(buffer, data);
	str = malloc(sizeof(char) * len + 1);
	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	if (buffer && buffer[i])
	{
		while (buffer[i + 1])
		{
			while ((ft_check_token(buffer[i], buffer[i + 1]) == 1) \
			&& buffer[i] != '\'' && buffer[i] != '"' && buffer[i])
			{
				str[j] = buffer[i];
				i++;
				j++;
			}

			if (ft_check_token(buffer[i], buffer[i + 1]) == 2)
			{
				str[j] = ' ';
				str[j + 1] = buffer[i];
				str[j + 2] = buffer[i];
				str[j + 3] = ' ';
				j += 4;
				i += 2;
			}
			if (buffer[i] == '\'' || buffer[i] == '"')
			{
				len = skip_quotes(buffer, i);
				while (j < len)
					str[j++] = buffer[i++];
			}
			else if (ft_check_token(buffer[i], buffer[i + 1]) == 0)
			{
				str[j] = ' ';
				str[j + 1] = buffer[i];
				str[j + 2] = ' ';
				j += 3;
				i += 1;
			}
		}
		str[j] = '\0';
		free (buffer);
	}
	return (str);
}
