/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:47:14 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/08 00:06:33 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_builtin(char *str)
{
    if (!ft_strcmp(str, "pwd"))
        return (4);
    if (!ft_strcmp(str, "echo"))
        return (5);
    return (0);
}

int redirect_in_builtin(char **cmds, t_data *data)
{
    (void)data;
    if (!ft_strcmp(cmds[0], "echo"))
    {
        start_echo(cmds);
        return (5);
    }
    return (-1);
}

void	print_echo(char **cmds, char *result)
{
	if (check_option(cmds[1]))
		ft_putstr(result);
	else
	{
		ft_putstr(result);
		write(1, "\n", 1);
	}
}