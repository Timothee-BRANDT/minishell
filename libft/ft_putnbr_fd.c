/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 14:02:46 by tbrandt           #+#    #+#             */
/*   Updated: 2021/10/26 17:04:15 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	if (nb == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
	}
	else
	{
		if (nb < 0)
		{
			nb = -nb;
			ft_putchar_fd('-', fd);
		}
		if (nb >= 0 && nb <= 9)
			ft_putchar_fd(nb + 48, fd);
		if (nb >= 10)
		{
			ft_putnbr_fd(nb / 10, fd);
			ft_putchar_fd(nb % 10 + 48, fd);
		}
	}
}
