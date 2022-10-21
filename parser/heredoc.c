/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:48:14 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/18 11:38:03 by tbrandt          ###   ########.fr       */
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

int	*create_files(t_list *list)
{
	int	i;
	int	j;
	int	*fd;
	
	i = 1;
	j = 0;
	fd = malloc(sizeof(int) * count_heredoc(list));
	while (i < count_heredoc(list) + 1)
	{
		fd[j] = open(ft_itoa(i), O_RDONLY | O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		i++;
		j++;
	}
	return (fd);
}

// when should i free my fd tab ???
int	start_heredoc(t_data *data)
{
	char	**tab;
	char	*str;
	int		*fd;
	int		i;
	int		j;

	tab = stock_delimitors(data->list, data);
	fd = create_files(data->list);
	i = 0;
	j = 0;
	while (i < count_heredoc(data->list))
	{
		while (1)
		{
			str = readline("> ");
			if (!ft_strcmp(str, tab[i]))
				break;
			ft_putstr_fd(str, fd[j]);
		}
		if (i == ft_strlen2d(tab))
			break;
		j++;
		i++;
	}
	return (0);
}