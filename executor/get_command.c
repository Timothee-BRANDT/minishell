/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:59:25 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/16 15:55:01 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	final_cmd_size(char **cmd)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	if (!cmd)
		return (0);
	while (cmd[i] && ft_strcmp(cmd[i], "|"))
	{
		if (is_redir(cmd[i]) && cmd[i + 2])
			i = i + 2;
		i++;
		result++;
	}
	return (result);
}

char	**extract_cmd(char **cmd, t_data *data)
{
	static int	j = 0;
	char		**final_cmd;
	int			i;
	int			*k;

	k = &j;
	i = 0;
	final_cmd = malloc(sizeof(char *) * (final_cmd_size(&cmd[j]) + 1));
	while (cmd[j] && ft_strcmp(cmd[j], "|"))
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
	if (j == ft_strlen2d(cmd))
		ft_bzero(&j, sizeof(int));
	return (final_cmd);
}

void	get_cmd_size(t_list *list, t_data *data)
{
	t_list	*tmp;

	tmp = list;
	data->cmd_size = 0;
	while (tmp)
	{
		tmp = tmp->next;
		data->cmd_size++;
	}
}

char	**get_cmd_from_list_v2(t_list *list, t_data *data)
{
	t_list	*tmp;
	char	**tab;
	int		i;

	tmp = list;
	get_cmd_size(data->list, data);
	tab = malloc(sizeof(char *) * (data->cmd_size + 1));
	i = 0;
	while (tmp)
	{
		if (tmp->content == NULL)
			tab[i] = ft_strdup(" ");
		else
			tab[i] = ft_strdup((char *)tmp->content);
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	get_cmd_from_list(t_list *list, t_data *data, t_cmd *cmd)
{
	t_list	*tmp;
	int		i;

	tmp = list;
	get_cmd_size(data->list, data);
	cmd->args = malloc(sizeof(char *) * (data->cmd_size + 1));
	i = 0;
	while (tmp)
	{
		if (tmp->content == NULL)
			cmd->args[i] = ft_strdup(" ");
		else
			cmd->args[i] = ft_strdup((char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	cmd->args[i] = NULL;
}
