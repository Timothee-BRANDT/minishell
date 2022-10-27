/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:37:57 by mmatthie          #+#    #+#             */
/*   Updated: 2022/10/21 15:24:39 by mmatthie         ###   ########.fr       */
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
