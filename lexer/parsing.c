/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:22:03 by mmatthie          #+#    #+#             */
/*   Updated: 2022/11/16 14:48:10 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_list(t_list	*lst)
{
	int	i;

	i = 0;
	if (!lst)
		printf("Empty List\n");
	while (lst != NULL)
	{
		printf("List %d:%s\n", i += 1, (char *)(lst->content));
		printf("pointeur: %p\n", (char *)lst->content);
		lst = lst->next;
	}
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src && src[i] && (i < n))
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

void	free_it(char	*str)
{
	free (str);
	str = NULL;
}
