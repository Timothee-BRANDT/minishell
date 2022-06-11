/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:17:39 by tbrandt           #+#    #+#             */
/*   Updated: 2021/10/20 15:28:45 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!((unsigned char *)s1) && !((unsigned char *)s2))
		return (0);
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	const void *s1 = "bonsoir";
	const void *s2 = "saloute";
	printf("Mine:%d\n", ft_memcmp(s1, s2, 3));
	printf("The:%d\n", memcmp(s1, s2, 3));
}*/
