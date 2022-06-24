/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:16:08 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/24 13:32:08 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;
	int		res;

	i = 0;
	res = 0;
	/*if (str[i] == '-')
		res--;*/
	while (str[i])
	{
		res++;
		i++;
	}
	return (res);
}
