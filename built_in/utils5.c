/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:23:18 by tbrandt           #+#    #+#             */
/*   Updated: 2022/09/27 12:56:41 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_cmd_count(t_list *cmd, t_data *data)
{
	t_list	*tmp;

	data->cmd_count = 1;
	data->pipe_count = 0;
	tmp = cmd;
	while (tmp->next)
	{
		if (is_pipe((char *)tmp->content))
		{
			data->pipe_count++;
			data->cmd_count++;
		}
		cmd = cmd->next;
		tmp = cmd;
	}
}

// quand je recupere le char ** de ma liste pour l'envoyer a execve, j'aurai deja retirer les redirections
void get_cmd_size(t_list *cmd, t_data *data)
{
    t_list *tmp;

    tmp = cmd;
    data->cmd_size = 0;
    while (tmp->next && !is_pipe((char *)cmd->content))
    {
        cmd = cmd->next;
        tmp = cmd;
        data->cmd_size++;
    }
}

char    **get_cmd_from_list(t_list *cmd, t_data *data)
{
	t_list	*tmp;
	char	**tab;
	int		i;

	tmp = cmd;
	get_cmd_size(data->cmd, data);
	tab = malloc(sizeof(char *) * data->cmd_size + 1);
	i = 0;
	while (tmp && !is_pipe((char *)cmd->content))
	{
		tab[i] = malloc(sizeof(char) * ft_strlen((char *)cmd->content) + 1);
		tab[i] = (char *)tmp->content;
		cmd = cmd->next;
		tmp = cmd;
		i++;
	}
	tab[i] = NULL;
	i = 0;
	while(tab[i])
	{
		printf("tab[i] :%s\n", tab[i]);
		i++;
	}
	return (tab);
}