/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:06:40 by tbrandt           #+#    #+#             */
/*   Updated: 2021/10/22 14:39:11 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = ft_strlen(src);
	if (!dest || !src || !size)
		return (i);
	i = 0;
	while ((i < (size - 1)) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (ft_strlen(src));
}
/*
#include<string.h>
#include<stdio.h>
int main()
{
	char src[] = "coucou";
	char dest[10]; 
	dest[0] = 0;
	dest[1] = 'A';
	memset(dest, 'A', 10);
	printf("%zu\n", strlcpy(dest, src, 1));
	printf("%zu\n", ft_strlcpy(dest, src, 1));
	printf("%s\n", dest);
}*/
