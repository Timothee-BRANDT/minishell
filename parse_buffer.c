/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_buffer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 16:36:23 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/14 14:38:32 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int check_quote(t_data *data)
{
	int	i;
	int check;
	int	tmp;

	i = -1;
	tmp = 0;
	while (data->buffer[++i])
	{
		if (data->buffer[i] == 34 || data->buffer[i] == 39)
		{
			tmp++;
			check = data->buffer[i];
			while (data->buffer[++i] != check && data->buffer[i] != '\0');
			if (data->buffer[i] == check)
				tmp--;
		}
	}
	if (tmp > 0)
			return(0);
	return (1);
}
