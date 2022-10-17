/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:23:18 by tbrandt           #+#    #+#             */
/*   Updated: 2022/09/28 10:01:36by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(char *key, t_list *env)
{
	t_list	*tmp;
	int		len;
	char	*tab;

	tmp = env;
	len = ft_strlen(key);
	while (tmp)
	{
		if (!ft_strncmp((char *)tmp->content, key, len))
		{
			tab = ft_get_value((char *)tmp->content);
			return (tab);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	free_list(void *ptr)
{
	t_list	*list;

	list = ptr;
	free(list);
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[i]: %s\n", tab[i]);
		i++;
	}
}

void	free_2_tab(char **tab1, char **tab2)
{
	free_tab(tab1);
	free_tab(tab2);
}

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[i] : %s\n", tab[i]);
		i++;
	}
}