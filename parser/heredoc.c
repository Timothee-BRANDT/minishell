/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:48:14 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/16 14:53:20 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_len(char **tab)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (!tab)
		return (0);
	while (tab[i] && ft_strcmp(tab[i], "|"))
	{
		i++;
		result++;
	}
	return (result);
}

int	count_heredoc(t_list *list)
{
	t_list	*tmp;
	int		count;

	if (!list->content)
		return (0);
	tmp = list;
	count = 0;
	while (tmp && tmp->next)
	{
		if (!ft_strcmp((char *)tmp->content, "<<"))
			count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**stock_delimitors(t_list *list, t_data *data)
{
	t_list	*tmp;
	char	**tab;
	int		i;

	(void)data;
	tab = malloc(sizeof(char *) * (count_heredoc(list) + 1));
	tmp = list;
	i = 0;
	while (tmp && tmp->next)
	{
		if (!ft_strcmp((char *)tmp->content, "<<"))
		{
			tab[i] = ft_strdup((char *)tmp->next->content);
			i++;
		}
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	free_and_close(char *str, int fd)
{
	free(str);
	close(fd);
}

int	start_heredoc(t_data *data)
{
	char	**tab;
	char	*str;
	int		i;
	int		fd;

	tab = stock_delimitors(data->list, data);
	i = -1;
	while (++i < count_heredoc(data->list))
	{
		fd = open(tab[i], O_RDONLY | O_WRONLY | \
		O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		while (1)
		{
			hd_norm();
			str = readline("> ");
			if (str == NULL || !ft_strcmp(str, tab[i]))
				break ;
			hd_norm_2(str, fd);
		}
		free_and_close(str, fd);
		if (i == ft_strlen2d(tab))
			break ;
	}
	free_tab(tab);
	return (0);
}
