/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:59:25 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/14 15:03:47 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**extract_cmd(char **cmd, t_data *data)
{
	int	i;
	static	int	j = 0;
	int	*k;
	char **final_cmd;

	final_cmd = malloc(sizeof(char *) * 500);
	k = &j;
	i = 0;
	while (cmd[j] && ft_strcmp(cmd[j], "|") != 0)
	{
		if (!ft_strcmp(cmd[j], ">"))
			extract_cmd_norm(k, cmd, data);
		if (!cmd[j] || !ft_strcmp(cmd[j], "|"))
			break ;
		final_cmd[i++] = ft_strdup(cmd[j]);
		j++;
	}
	if (cmd[j] && ft_strcmp(cmd[j], "|") == 0)
		j++;
	final_cmd[i] = NULL;
	if(j == ft_strlen2d(cmd))
		ft_bzero(&j, sizeof(int));
	return (final_cmd);
}

// this function count the number of commands and the number of pipes in the buffer;
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

// quand je recupere le char ** de ma liste pour l'envoyer a execve, j'aurai deja retirer les redirections
// this function returns the size of the first commands before the pipe
// ls -la | grep yo
// cmd_size = 2;
void get_cmd_size(t_list *list, t_data *data)
{
    t_list *tmp;

    tmp = list;
    data->cmd_size = 0;
    while (tmp)
    {
        tmp = tmp->next;
        data->cmd_size++;
    }
}

// function return first command before pipe in a char **, need to pass it to execve
// ls -la | grep yo
// returns tab[0] = ls; tab[1] = -la; tab[2] = NULL
void	get_cmd_from_list(t_list *list, t_data *data, t_cmd *cmd)
{
	t_list	*tmp;
	int		i;

	tmp = list;
	get_cmd_size(data->list, data);
	cmd->args = malloc(sizeof(char *) * data->cmd_size + 1);
	i = 0;
	while (tmp)
	{
		cmd->args[i] = ft_strdup((char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	cmd->args[i] = NULL;
}

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