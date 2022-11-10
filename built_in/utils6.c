/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:47:14 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/10 15:53:02 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_builtin(char *str)
{
    if (!ft_strcmp(str, "env"))
        return (1);
    if (!ft_strcmp(str, "export"))
        return (2);
    if (!ft_strcmp(str, "pwd"))
        return (3);
    if (!ft_strcmp(str, "echo"))
        return (4);
    if (!ft_strcmp(str, "cd"))
        return (5);
    if (!ft_strcmp(str, "exit"))
        return (6);
    if (!ft_strcmp(str, "unset"))
        return (7);
    return (0);
}

int redirect_in_builtin(char **cmds, t_data *data)
{
	if (!cmds)
		return (1);
	if (is_export(cmds, data))
		return (1);
	else if (is_env(cmds, data))
		return (1);
	else if (is_unset(cmds, data))
		return (1);
	else if (is_cd(cmds, data))
		return (1);
	else if (is_pwd(cmds, data))
		return (1);
	else if (is_echo(cmds, data))
		return (1);
	return (0);
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