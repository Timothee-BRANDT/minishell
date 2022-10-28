/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:59:25 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/28 14:40:01 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	**extract_cmd(char **cmd, t_data *data)
{
	static	int	j = 0;
	char		**final_cmd;
	int			i;
	int			*k;

	final_cmd = malloc(sizeof(char *) * 500);
	k = &j;
	i = 0;
	while (cmd[j] && ft_strcmp(cmd[j], "|") != 0)
	{
		if (cmd[j][0] == '\0')
			j++;
		check_all_redirection(cmd, k, data);
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
