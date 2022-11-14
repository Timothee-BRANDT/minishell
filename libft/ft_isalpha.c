/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 13:47:06 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/14 14:34:21 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (c >= '0' && c <= '9')
	{
		printf("char :%c\n", c);
		return (0);
	}
	else
	{
		printf("char :%c\n", c);
		return (1);
	}
}

int	ft_isnum_key(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			return (0);
		i++;
	}
	return (1);
}
