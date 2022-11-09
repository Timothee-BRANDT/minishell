/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 15:47:14 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/09 15:27:29 by tbrandt          ###   ########.fr       */
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
    return (0);
}

int redirect_in_builtin(char **cmds, t_data *data)
{
    (void)data;
    char    *result;
    result = NULL;
	if (cmds[0] && !ft_strcmp(cmds[0], "env"))
	{
		ft_print_env(data->env);
		return (1);
	}
    if ((cmds[0] && !ft_strcmp(cmds[0], "export") && (!cmds[1] || !ft_strcmp(cmds[1], "|"))))
    {
        ft_print_env(data->export);
        return (2);

    }
    if (!ft_strcmp(cmds[0], "echo"))
    {
        start_echo(cmds);
        return (5);
    }
	if (!ft_strcmp(cmds[0], "pwd"))
	{
		result = get_env_v2("PWD", data->export);
		ft_putstr_fd(result, 1);
		free(result);
		return (1);
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