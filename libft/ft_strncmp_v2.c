/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_v2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 15:52:34 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/14 14:36:26 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp_v2(const char *s1, const char *s2, size_t n)
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
