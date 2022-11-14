/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 02:40:15 by mmatthie          #+#    #+#             */
/*   Updated: 2022/11/01 18:36:59 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	double_redir(t_data	*data, char	*str, char	*buffer)
{
	str[data->j_space] = ' ';
	str[data->j_space + 1] = buffer[data->i_space];
	str[data->j_space + 2] = buffer[data->i_space];
	str[data->j_space + 3] = ' ';
	data->j_space += 3;
	data->i_space += 2;
}

void	set_redir(t_data	*data, char	*str, char	*buffer)
{
	str[data->j_space] = ' ';
	if (ft_check_token(buffer[data->i_space]) == 0)
	{
		data->j_space++;
		while (ft_check_token(buffer[data->i_space]) == 0)
		{
			str[data->j_space] = buffer[data->i_space];
			data->j_space++;
			data->i_space++;
		}
		str[data->j_space] = ' ';
		data->j_space++;
	}
}

int	fill_quotes(char *dest, char	*buffer, t_data	*data)
{
	int	tmp;

	tmp = buffer[data->i_space];
	dest[data->j_space] = buffer[data->i_space];
	data->i_space++;
	data->j_space++;
	if (buffer && buffer[data->i_space])
	{
		while (buffer[data->i_space] && (buffer[data->i_space] != tmp))
		{
			dest[data->j_space] = buffer[data->i_space];
			data->i_space++;
			data->j_space++;
		}
		dest[data->j_space] = buffer[data->i_space];
		data->j_space++;
	}
	return (data->i_space + 1);
}
