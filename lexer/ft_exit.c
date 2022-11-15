/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:24:53 by mmatthie          #+#    #+#             */
/*   Updated: 2022/11/15 16:37:01 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_exit_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	is_exit(char **tab)
{
	if (!ft_strcmp(tab[0], "exit"))
	{
		if (tab[1] && check_exit_arg(tab[1]))
		{
			write(1, "exit\n", 5);
			ft_putstr_fd("bash: exit: numeric argument required", 2);
			g_glo.g_signum = 255;
			exit(255);
		}
		else
			exit(ft_atoi(tab[1]));
		if (ft_strlen2d(tab) > 2)
		{
			write(1, "exit\n", 5);
			ft_putstr_fd("Bibishell: exit: too many arguments", 2);
			g_glo.g_signum = 1;
			return (0);
		}
		else if (ft_strlen2d(tab) == 1)
		{
			g_glo.g_signum = 1;
			exit(1);
		}
	}
	return (1);
}
