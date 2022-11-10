/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:11:49 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/10 17:10:58 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    is_pwd(char **tab, t_data *data)
{
	char *result;

	if (tab[0] && !ft_strcmp(tab[0], "pwd") && !data->check_pipe)
	{
		result = get_env_v2_export("PWD", data);
		if (!result)
		{
			printf("return 1\n");
			return (1);
		}
		ft_putstr(result);
		ft_putchar('\n');
		free(result);
		return (0);
	}
	return (0);
}