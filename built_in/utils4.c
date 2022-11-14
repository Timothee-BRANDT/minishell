/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:12:30 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/14 11:51:42 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**list_to_tab(t_list *cmd)
{
	t_list	*tmp;
	char	**tab;
	int		i;

	tmp = cmd;
	tab = malloc(sizeof(char *) * (ft_lstsize(cmd) + 1));
	i = 0;
	while (tmp && !is_built_in((char *)cmd->content) \
	&& !is_token((char *)cmd->content))
	{
		tab[i] = malloc(sizeof(char) * ft_strlen((char *)tmp->content) + 1);
		tab[i] = (char *)tmp->content;
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

int	is_built_in(void *content)
{
	if (!ft_strcmp((char *)content, "unset"))
		return (1);
	if (!ft_strcmp((char *)content, "cd"))
		return (1);
	if (!ft_strcmp((char *)content, "exit"))
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

int	is_redir(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[0] == '<' && str[1] == '<')
			return (1);
		else if (str[0] == '>' && str[1] == '>')
			return (2);
		else if (str[0] == '<')
			return (3);
		else if (str[0] == '>')
			return (4);
		i++;
	}
	return (0);
}

int	is_pipe(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[0] == '|')
			return (1);
		i++;
	}
	return (0);
}
