/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:01:36 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/14 14:41:10 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    extract_cmd_norm(int *k, char **cmd, t_data *data)
{
	data->fd_out = open(cmd[*k + 1], O_WRONLY | O_CREAT | O_NOCTTY | \
	O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	*k = *k + 2;
	while (cmd[*k] && !ft_strcmp(cmd[*k], ">"))
	{
		data->fd_out = open(cmd[*k + 1], O_WRONLY | O_CREAT | O_NOCTTY | \
		O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		*k = *k + 2;
    }
}