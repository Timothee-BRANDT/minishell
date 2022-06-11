/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:49:37 by tbrandt           #+#    #+#             */
/*   Updated: 2021/10/20 10:50:02 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	src;
	unsigned char	dest;

	i = 0;
	if (!n)
		return (n);
	src = (unsigned char)s1[i];
	dest = (unsigned char)s2[i];
	while ((src && dest) && (i < n))
	{
		src = (unsigned char)s1[i];
		dest = (unsigned char)s2[i];
		if (src != dest)
			return (src - dest);
		i++;
	}
	return (src - dest);
}
/*
#include <stdio.h>
int main()
{
	char s1[] = "sonsoir";
	char s2[] = "salut";
	printf("%d", ft_strncmp(s1, s2, 2));
}*/
