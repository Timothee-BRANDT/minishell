/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:08:03 by tbrandt           #+#    #+#             */
/*   Updated: 2021/10/26 17:00:30 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*source;
	size_t				i;

	if (src == NULL && dst == NULL)
		return (NULL);
	i = 0;
	dest = (unsigned char *) dst;
	source = (const unsigned char *) src;
	while (i < n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dst);
}
/*
#include<stdio.h>
int main()
{
	unsigned char src [] = {"fufu"};
	unsigned char dst [] = {"bonsoir ahaha"};
	ft_memcpy(dst, src, 2);

	printf("%s", dst);
}*/
