/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 13:43:30 by tbrandt           #+#    #+#             */
/*   Updated: 2021/10/26 16:00:23 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t		i;
	size_t		j;
	size_t		dest_len;
	size_t		src_len;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	j = 0;
	if (size <= ft_strlen(dest))
		return (ft_strlen(src) + size);
	i = ft_strlen(dest);
	while (src[j] != '\0' && j < (size - dest_len - 1))
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (src_len + dest_len);
}
/*
#include<stdio.h>
#include <string.h>
int main()
{
	char dest[30];
	char *src = (char *)"AAA";
	memset(dest, 'C', 5);
	printf("%zu\n", ft_strlcat(dest, src, 5));
	printf("%zu\n", strlcat(dest, src, 5));
	printf("%s", dest);
}*/
