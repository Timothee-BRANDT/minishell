/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:48:14 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/17 11:20:20 by tbrandt          ###   ########.fr       */
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
	tab = malloc(sizeof(char *) * count_heredoc(list) + 1);
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

int	start_heredoc(t_data *data)
{
	char	**tab;
	char	*str;
	int		fd;
	int		i;

	i = 0;
	tab = stock_delimitors(data->list, data);
	fd = open(".h_doc", O_RDONLY | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1)
		return (on_error("Open heredocfile failed\n", 1));
	while (1)
	{
		str = readline("> ");
		ft_putstr_fd(str, fd);
		if (!ft_strcmp(str, tab[i]))
			i++;
		if (i == ft_strlen2d(tab))
			break;
	}
	return (0);
}