/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:11:49 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/08 00:06:14 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    is_pwd(char **tab, t_data *data)
{
	char *result;

	if (!ft_strcmp(tab[0], "pwd"))
	{
		result = get_env_v2("PWD", data->env);
		ft_putstr_fd(result, 1);
		free(result);
		return (1);
	}
	return (0);
}