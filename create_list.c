/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:54:28 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/10 18:02:17 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_space(char *buffer)
{
	int	i;

	i = 0;
	while(buffer[i])
	{
		if (buffer[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

t_list *create_list(char **buffer_splited)
{
	t_list	*lst;
	int		i;

	i = 1;
	lst = ft_lstnew(buffer_splited[0]);
	while (buffer_splited[i])
	{
		ft_lstadd_back(&lst, ft_lstnew(buffer_splited[i]));
		i++;
	}
	return (lst);
}
