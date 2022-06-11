/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:31:59 by tbrandt           #+#    #+#             */
/*   Updated: 2021/10/18 17:37:23 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 & c <= 127)
		return (1);
	else
		return (0);
}
/*
#include<stdio.h>
int main()
{
	printf("%d", ft_isascii(110));
	printf("\n");
	printf("%d", isascii(110));
}*/
