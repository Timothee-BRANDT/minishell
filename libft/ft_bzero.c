/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 17:43:13 by tbrandt           #+#    #+#             */
/*   Updated: 2021/10/26 16:50:10 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	if (n == 0)
		return ;
	i = 0;
	str = (unsigned char *) s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}
/*
#include <stdio.h>
int main()
{
	unsigned char test [] = {'b', 't', 'j', 'k'};
	ft_bzero(test, 4);

	int i = 0;
	while(i < 4)
	{
		printf("%d\n", test[i]);
		i++;
	}
}*/
