/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 15:54:28 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/16 15:08:01 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_list(t_list	*lst, char	*str)
{
	t_list	*li;

	li = NULL;
	if (lst == NULL)
	{
		lst = ft_lstnew(str);
		return(lst);
	}
	else
	{
		li = ft_lstnew(str);
		ft_lstadd_back(&lst, li);
		return (lst);
	}
	return (lst);
}

t_list	*get_word_in_list(char	*buffer, t_data	*data)
{
	t_list	*lst;
	int	i;

	i = -1;
	data->count = 0;
	lst = NULL;
	//printf("data->count : %d\n", data->count);
	while (data->count < (int)ft_strlen(buffer))
	{
		while (ft_isspace(buffer[data->count]))
			data->count++;
		if (buffer[data->count] != '"' && buffer[data->count] != '\'' && buffer[data->count] != '\0' && buffer[data->count] != ' ')
		{
			data->count = get_word(buffer, data);
			lst = ft_list(lst, data->first);
		}
		/*else if (buffer[data->count] != '"' || buffer[data->count] != '\'')
		{
		}*/
	}
	return (lst);
}

int	get_word(char	*str, t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = data->count;
	while (str[j] != '"' && str[j] != '\'' && str[j] != '\0' && str[j] != ' ')
	{
		j++;
		i++;
	}
	data->first = ft_calloc(1, i);
	data->first = ft_strncpy(data->first, &str[data->count], i);
	//if (str[j] == '"' || str[j] == '\'')
		//j = pre_join(str, data, j);
	data->count = j;
	return (data->count + 1);
}
