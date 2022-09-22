/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:12:30 by tbrandt           #+#    #+#             */
/*   Updated: 2022/09/22 10:20:25 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_built_in(char *str)
{
    if (ft_strcmp(str, "export") == 0)
        return (1);
    else if (ft_strcmp(str, "env") == 0)
        return (1);
    else if (ft_strcmp(str, "unset") == 0)
        return (1);
    else if (ft_strcmp(str, "pwd") == 0)
        return (1);
    else if (ft_strcmp(str, "echo") == 0)
        return (1);
    else if (ft_strcmp(str, "cd") == 0)
        return (1);
    else if (ft_strcmp(str, "exit") == 0)
        return (1);
    return (0);
}