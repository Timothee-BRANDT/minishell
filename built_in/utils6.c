/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:47:14 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/01 11:55:11 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_builtin(char *str)
{
    if (!ft_strcmp(str, "export"))
        return (1);
    if (!ft_strcmp(str, "env"))
        return (2);
    if (!ft_strcmp(str, "unset"))
        return (3);
    if (!ft_strcmp(str, "pwd"))
        return (4);
    if (!ft_strcmp(str, "echo"))
        return (5);
    if (!ft_strcmp(str, "cd"))
        return (6);
    if (!ft_strcmp(str, "exit"))
        return (7);
    return (0);
}

int redirect_in_builtin(char **cmds, t_data *data)
{
    (void)data;
    if (!ft_strcmp(cmds[0], "export"))
        return (1);
    // export function
    if (!ft_strcmp(cmds[0], "env"))
        return (2);
    // env function
    if (!ft_strcmp(cmds[0], "unset"))
        return (3);
    // unset function
    if (!ft_strcmp(cmds[0], "pwd"))
        return (4);
    if (!ft_strcmp(cmds[0], "echo"))
    {
        start_echo(cmds);
        return (5);
    }
    if (!ft_strcmp(cmds[0], "cd"))
        return (6);
    if (!ft_strcmp(cmds[0], "exit"))
        return (7);
    return (-1);
}