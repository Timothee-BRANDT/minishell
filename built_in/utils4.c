/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:12:30 by tbrandt           #+#    #+#             */
/*   Updated: 2022/09/22 11:06:01 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    **list_to_tab(t_list *cmd)
{
	t_list *tmp;
    char	**tab;
	int		i;

	tmp = cmd;
	tab = malloc(sizeof(char *) * ft_lstsize(cmd) + 1);
	i = 0;
	while (tmp && !is_built_in((char *)cmd->content) && !is_token((char *)cmd->content))
	{
		tab[i] = malloc(sizeof(char) * ft_strlen((char *)tmp->content) + 1);
		tab[i] = (char *)tmp->content;
		cmd = cmd->next;
		tmp = cmd;
		i++;
	}
    tab[i] = NULL;
	return (tab);
}

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