/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:12:20 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/11 11:07:31 by mmatthie         ###   ########.fr       */
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
	while (buffer[data->count] && ft_isspace(buffer[data->count]))
		data->count++;
	if (buffer[data->count] != ' ' || buffer[data->count] == '\0')
		lst = ft_list(lst, data);
	ft_manage(data->get_word);
	return (lst);
}

void	set_data(t_data	*data)
{
	data->token = 0;
	data->indicate = 0;
	data->first = NULL;
	data->second = NULL;
	data->join = NULL;
	data->buffer = NULL;
	data->get_word = NULL;
	data->i_space = 0;
	data->j_space = 0;
	data->res_space = 0;
	data->index_space = 0;
	data->space_len = 0;
	data->indicate_expend = 0;
	data->i_get = 0;
	data->j_get = 0;
}

void	print_it(char	*ptr)
{
	if (ptr == NULL)
		printf("ptr is NULL\n");
	else
		printf("%s\n", ptr);
}
