/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils10.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 12:11:30 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/14 12:19:40 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd(t_data *data, char *pwd)
{
	change_pwd_export(data);
	change_pwd_env(data);
	change_oldpwd_export(data, pwd);
	change_oldpwd_env(data, pwd);
}

int	error_open(char **tab, char *pwd)
{
	if (errno == EACCES)
	{
		free(pwd);
		printf("Bibishell: cd : %s: Permission denied\n", tab[1]);
		return (1);
	}
	else if (errno == ENOENT)
	{
		free(pwd);
		printf("Bibishell: cd : %s: No such file \
		or directory\n", tab[1]);
		return (1);
	}
	return (0);
}
