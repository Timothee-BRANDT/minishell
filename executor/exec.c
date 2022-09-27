/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:20:28 by tbrandt           #+#    #+#             */
/*   Updated: 2022/09/27 11:20:34 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_in_analyzer(t_list **cmd, t_data	*data)
{
	if (!(*cmd))
		return ;
    if (is_built_in((*cmd)->content))
    {
		if (ft_strcmp((*cmd)->content, "env") == 0)
			ft_print_env(data->env);
		if (ft_strcmp((*cmd)->content, "export") == 0 && !data->cmd->next)
			ft_print_env(data->export);
		if (ft_strcmp((*cmd)->content, "export") == 0 && data->cmd->next)
			export_name(cmd, data, 0);
		if (ft_strcmp((*cmd)->content, "unset") == 0 && (*cmd)->next)
    	{
    		unset_name_export(&data->export, cmd);
    		unset_name_env(&data->env, cmd);
		}
	}
}

void	exec_command(t_list	**cmd, t_data	*data)
{
	char	**paths;
	char	**cmds;
	char	*good_cmd;
	char	**env;

	paths = get_all_path(data);
	cmds = list_to_tab(*cmd);
	env = list_to_tab(data->env);
	good_cmd = get_correct_cmd(paths, cmds);
	if (!good_cmd)
	{
		free_tab(cmds);
		free_tab(paths);
		printf("Shell: command not found.\n");
		return ;
	}
	if (execve(good_cmd, cmds, env) == -1)
		write(2, "Command execution failed\n", 25);
}
