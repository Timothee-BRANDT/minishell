/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:12:20 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/22 15:30:08 by tbrandt          ###   ########.fr       */
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
	while (ft_isspace(buffer[data->count]))
		data->count++;
	if (buffer[data->count] != ' ' || buffer[data->count] == '\0')
		lst = ft_list(lst, data);
	return (lst);
}
