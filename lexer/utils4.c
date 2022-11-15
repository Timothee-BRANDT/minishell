/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:17:57 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/15 16:38:04 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	get_len_v2(int n)
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

char	*ft_itoa_v2(int n)
{
	char	*res;
	int		len_res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len_res = (get_len_v2(n));
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
