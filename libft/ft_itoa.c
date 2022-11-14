/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:11:13 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/05 23:57:03 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

/*int	len(int n)
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

	str = malloc(sizeof(char) * len(n) + 1);
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	i = len(n) + 1;
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
}*/

static int	get_len(int n)
{
	int	res;

	res = 0;
	if (!n)
		return (1);
	if (n < 0)
		res++;
	while (n)
	{
		n /= 10;
		res++;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		len_res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len_res = (get_len(n));
	res = malloc(sizeof(char) * len_res + 1);
	if (!res)
		return (NULL);
	if (n == 0 || (!n))
		res[0] = '0';
	if (n < 0)
	{
		res[0] = '-';
		n *= -1;
	}
	res[len_res] = '\0';
	while (n)
	{
		res[--len_res] = (n % 10) + 48;
		n /= 10;
	}
	return (res);
}