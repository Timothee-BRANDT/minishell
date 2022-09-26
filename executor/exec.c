/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:20:28 by tbrandt           #+#    #+#             */
/*   Updated: 2022/09/22 13:35:23 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
