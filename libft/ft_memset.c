/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:32:56 by tbrandt           #+#    #+#             */
/*   Updated: 2021/10/19 09:48:25 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	if (!s)
		return (NULL);
	i = 0;
	str = (unsigned char *) s;
	while (i < n)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (str);
}

/*#include <stdio.h>
int main()
{
	unsigned char test [] = {'b', 'w', 'f', 'q', 'p', 'l'};
	ft_memset(test, 5, 6);

	int i = 0;
	while(i < 6)
	{
		printf("%d\n", test[i]);
		i++;
	}
}*/
