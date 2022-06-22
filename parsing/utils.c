/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:12:32 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/22 18:52:22 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_list(t_list	*lst)
{
	if (!lst)
		printf("Empty List\n");
	while (lst != NULL)
	{
		printf("List:%s\n", (char *)(lst->content));
		lst = lst->next;
	}
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((src[i] != '\0') && (i < n))
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

int	check_quote(char	*buffer)
{
	int	i;
	int	check;
	int	tmp;

	i = 0;
	tmp = 0;
	if (!buffer)
		return (1);
	while (buffer && buffer[i])
	{
		if (buffer[i] == 34 || buffer[i] == 39)
		{
			tmp++;
			check = buffer[i];
			i++;
			while (buffer[i] != check && buffer[i] != '\0')
				i++;
			if (buffer[i] == check)
				tmp--;
		}
		i++;
	}
	if (tmp != 0)
		return (0);
	return (1);
}

int	ft_isspace(int c)
{
	if (((c == '\n') || (c == '\v') || (c == '\t')) \
	|| ((c == '\r') || (c == '\f') || (c == ' ')))
		return (1);
	return (0);
}

int	get_quotes(char	*buffer, t_data	*data, int count)
{
	int	i;
	int	j;

	j = 0;
	data->token = buffer[count];
	i = count;
	count++;
	while (buffer[++i] != data->token && buffer[i] != '\0')
		j++;
	data->first = ft_calloc(1, j);
	data->first = ft_strncpy(data->first, &buffer[count], j);
	i++;
	if (buffer[i] != ' ' || buffer[i] != '\0')
		count = get_join(buffer, count, i, data);
	else
	{
		data->get_word = ft_calloc(1, ft_strlen(data->first));
		data->get_word = ft_strncpy \
		(data->get_word, data->first, ft_strlen(data->first));
		count = i;
	}
	return (count);
}
