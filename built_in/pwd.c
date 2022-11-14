/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:11:49 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/14 10:30:44 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_pwd_main(char **tab, t_data *data)
{
	char	pwd[256];
	char	*result;

	if (tab[0] && !ft_strcmp(tab[0], "pwd") && !data->check_pipe)
	{
		result = getcwd(pwd, sizeof(pwd));
		if (!result)
			return (-1);
		ft_putstr(result);
		ft_putchar('\n');
		return (0);
	}
	return (1);
}

int	is_pwd_child(char **tab, t_data *data)
{
	char	pwd[256];
	char	*result;

	(void)data;
	if (tab[0] && !ft_strcmp(tab[0], "pwd"))
	{
		result = getcwd(pwd, sizeof(pwd));
		if (!result)
			return (-1);
		ft_putstr(result);
		ft_putchar('\n');
		return (0);
	}
	return (1);
}
