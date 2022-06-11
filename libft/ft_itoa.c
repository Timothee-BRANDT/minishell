/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:11:13 by tbrandt           #+#    #+#             */
/*   Updated: 2022/03/14 17:07:07 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	len(int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n = n * -1;
		len++;
	}
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * len(n));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	i = len(n);
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1 ;
	}
	str[i] = '\0';
	i--;
	while (n > 0)
	{
		str[i] = (n % 10) + 48;
		n = n / 10;
		i--;
	}
	return (str);
}
