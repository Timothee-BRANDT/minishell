/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 13:49:55 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/03 16:21:48 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

size_t	count_words(const char *str, char c)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (i && str[i - 1] == c && str[i] != c)
			j++;
		if (!i && str[i] != c)
			j++;
		i++;
	}
	return (j);
}

size_t	size_words(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

char	**ft_split(const char *str, char c)
{
	size_t		i;
	size_t		j;
	size_t		k;
	char		**tab;

	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	k = 0;
	tab = malloc(sizeof (char *) * (count_words((char *)str, c) + 1));
	if (!tab)
		return (NULL);
	while (++i < count_words((char *)str, c))
	{
		tab[i] = malloc(sizeof(char) * (size_words(((str + j + 1)), c)) + 1);
		k = 0;
		while (str[j] && str[j] == c)
			j++;
		while (str[j] && str[j] != c)
			tab[i][k++] = str[j++];
		tab[i][k] = 0;
	}
	tab[i] = NULL;
	return (tab);
}
