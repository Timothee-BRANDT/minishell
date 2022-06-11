/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:14:16 by tbrandt           #+#    #+#             */
/*   Updated: 2021/10/29 14:27:48 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t		i;
	size_t		j;
	int			k;
	char		*str;

	if (!s1 || !set)
		return (NULL);
	str = (char *) s1;
	i = 0;
	k = 0;
	j = ft_strlen(s1) - 1;
	while (is_in_set(s1[i], set))
		i++;
	if (i == ft_strlen(s1))
		return (ft_strdup(""));
	while (is_in_set(s1[j], set))
		j--;
	str = malloc(sizeof(char) * (j - i) + 1);
	if (!str)
		return (NULL);
	while (i <= j)
		str[k++] = s1[i++];
	str[k] = '\0';
	return (str);
}
/*
#include <stdio.h>
int main()
{
	printf("%s", ft_strtrim("      xxxtripouille   xxx", " x"));
}*/
