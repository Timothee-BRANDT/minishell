/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:24:53 by mmatthie          #+#    #+#             */
/*   Updated: 2022/11/15 17:31:40 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_str(char *str)
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

int	check_exit_arg(char **tab)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] < '0' || tab[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_exit(char **tab)
{
	if (tab[0] && !ft_strcmp(tab[0], "exit"))
	{
		if (ft_strlen2d(tab) == 1)
		{
			write(1, "exit\n", 5);
			g_glo.g_signum = 1;
			exit(0);
		}
		if (!check_str(tab[1]) && ft_strlen2d(tab) > 2)
		{
			ft_putstr_fd("exit\nBibishell: exit: too many arguments", 2);
			g_glo.g_signum = 1;
			return (0);
		}
		if (check_exit_arg(&tab[1]))
		{
			ft_putstr_fd("exit\nbash: exit: numeric argument required", 2);
			g_glo.g_signum = 255;
			exit(255);
		}
		else
			exit(ft_atoi(tab[1]));
	}
	return (1);
}
