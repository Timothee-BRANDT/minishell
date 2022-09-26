/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:12:30 by tbrandt           #+#    #+#             */
/*   Updated: 2022/09/26 14:15:18 by tbrandt          ###   ########.fr       */
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

int is_built_in(void *content)
{
    if (ft_strcmp((char *)content, "export") == 0)
        return (1);
    if (ft_strcmp(content, "env") == 0)
        return (1);
    if (ft_strcmp(content, "unset") == 0)
        return (1);
    if (ft_strcmp(content, "pwd") == 0)
        return (1);
    if (ft_strcmp(content, "echo") == 0)
        return (1);
    if (ft_strcmp(content, "cd") == 0)
        return (1);
    if (ft_strcmp(content, "exit") == 0)
        return (1);
    return (0);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
}