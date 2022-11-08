/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:48:14 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/08 18:37:48 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int count_heredoc(t_list *list)
{
    t_list	*tmp;
    int		count;

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

	while(tmp && tmp->next)
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

// when should i free my fd tab ???
int	start_heredoc(t_data *data)
{
	char	**tab;
	char	*str;
	int		i;
	int		fd;

	tab = stock_delimitors(data->list, data);
	i = 0;
	while (i < count_heredoc(data->list))
	{
		fd = open(tab[i], O_RDONLY | O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		while (1)
		{
			str = readline("> ");
			if (!ft_strcmp(str, tab[i]))
				break;
			ft_putstr_fd_free(str, fd);
		}
		free(str);
		close(fd);
		i++;
		if (i == ft_strlen2d(tab))
			break;
	}
	free_tab(tab);
	return (0);
}