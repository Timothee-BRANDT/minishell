/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:06:58 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/14 14:07:17 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**lst_to_tab(t_list *list, t_data *data)
{
	t_list	*tmp;
	char	**tab;
	int		i;

	tmp = list;
	get_cmd_size(data->list, data);
	tab = malloc(sizeof(char *) * data->cmd_size + 1);
	i = 0;
	while (tmp)
	{
		tab[i] = ft_strdup((char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	check_all_redirection(char **cmd, int *k, t_data *data)
{
	while (is_redir(cmd[*k]))
	{
		if (is_redir(cmd[*k]) == 1 || is_redir(cmd[*k]) == 3)
			redir_in_manager(k, cmd, data);
		if (is_redir(cmd[*k]) == 2 || is_redir(cmd[*k]) == 4)
			redir_out_manager(k, cmd, data);
	}
}

void	get_cmd_count(t_list *list, t_data *data)
{
	t_list	*tmp;

	data->cmd_count = 1;
	data->pipe_count = 0;
	tmp = list;
	while (tmp)
	{
		if (is_pipe((char *)tmp->content))
		{
			data->pipe_count++;
			data->cmd_count++;
		}
		tmp = tmp->next;
	}
}
