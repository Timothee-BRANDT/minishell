/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:08:29 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/27 11:05:29 by mmatthie         ###   ########.fr       */
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
	data->second = ft_calloc(1, j + 1);
	data->second = ft_strncpy(data->second, &buffer[count], j);
	data->join = ft_join_free_ss(data->first, data->second);
	//printf("data->join : %s\n", data->join);
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

t_list	*get_word_in_list(char	*buffer, t_data	*data)
{
	t_list	*lst;

	lst = NULL;
	data->count = 0;
	if (buffer && buffer[0])
	{
		while (data->count < (int)ft_strlen(buffer))
		{
			while (ft_isspace(buffer[data->count]))
				data->count++;
			if (buffer[data->count] != '"' && buffer[data->count] \
			!= '\'' && buffer[data->count] != '\0')
				data->count = get_word(buffer, data, data->count);
			else if (buffer[data->count] == '"' || buffer[data->count] == '\'')
				data->count = get_quotes(buffer, data, data->count);
			if (buffer[data->count] == ' ' || buffer[data->count] == '\0')
				lst = get_in_list(buffer, data, lst);
		}
	}
	return (lst);
}

void	ft_free_list(t_list	**lst)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}
