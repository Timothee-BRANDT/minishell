/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:08:29 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/06 13:06:36 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_list(t_list	*lst, t_data	*data)
{
	if (lst == NULL)
		lst = ft_lstnew(data->get_word);
	else
		ft_lstadd_back(&lst, ft_lstnew(data->get_word));
	return (lst);
}

int	make_second(char	*buffer, t_data *data, int count)
{
	int	j;
	int	i;

	j = 0;
	i = count;
	while (buffer[i] != data->token && buffer[i])
	{
		j++;
		i++;
	}
	data->second = ft_calloc(1, j);
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
	count = i;
	return (count);
}
