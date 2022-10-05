/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:20:28 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/05 08:33:46 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_in_analyzer(t_list **list, t_data	*data)
{
	if (!(*list))
		return ;
    if (is_built_in((*list)->content))
    {
		if (ft_strcmp((*list)->content, "env") == 0)
			ft_print_env(data->env);
		if (ft_strcmp((*list)->content, "export") == 0 && !data->list->next)
			ft_print_env(data->export);
		if (ft_strcmp((*list)->content, "export") == 0 && data->list->next)
			export_name(list, data, 0);
		if (ft_strcmp((*list)->content, "unset") == 0 && (*list)->next)
    	{
    		unset_name_export(&data->export, list);
    		unset_name_env(&data->env, list);
		}
	}
}

void	exec_command(t_cmd *cmd, t_data	*data)
{
	char	**paths;
	char	*good_cmd;
	char	**env;

	paths = get_all_path(data);
	env = list_to_tab(data->env);
	good_cmd = get_correct_cmd(paths, cmd->args);
	int i = 0;
	while(cmd->args[i])
	{
		dprintf(data->tmp_in, "Args :%s\n", cmd->args[i]);
		i++;
	}
	if (!good_cmd)
	{
		free_tab(cmd->args);
		free_tab(paths);
		printf("Shell: command not found.\n");
		return ;
	}
	if (execve(good_cmd, cmd->args, env) == -1)
		write(2, "Command execution failed\n", 25);
}
