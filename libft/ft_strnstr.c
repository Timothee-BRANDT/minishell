/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:24:20 by tbrandt           #+#    #+#             */
/*   Updated: 2021/10/22 09:38:52 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!needle[i])
		return ((char *)haystack);
	while (haystack[i])
	{
		j = 0;
		while (needle[j] == haystack[i + j] && (i + j) < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>
int main()
{
	char haystack[30] = "aaabcabcd";	
	char needle [10] = "cd";
	printf("Mine: %s\n", ft_strnstr(haystack, needle, 30));
	printf("The: %s", strnstr(haystack, needle, 30));
}*/
