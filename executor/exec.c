/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:20:28 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/08 17:25:56y tbrandt          ###   ########.fr       */
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

void	exec_command(char **cmds, t_data	*data)
{
	char	**paths;
	char	*good_cmd;
	char	**env;

	paths = get_all_path(data);
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

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[i] : %s\n", tab[i]);
		i++;
	}
}

int	start_exec(t_cmd *cmd, t_data *data)
{
	int i;
	pid_t pid;
	int	status;
	char **cmds;

	i = -1;
	status = 0;
	while (++i < data->cmd_count)
	{
		if (i == data->cmd_count - 1)
			redir_fd_out(data);
		else
			create_pipe(data);
    	get_cmd_from_list(data->list, data, cmd);
		cmds = extract_cmd(cmd->args, data);
		pid = fork();
		if (pid == 0)
			dup_child_exec(cmds, data);
		else
			dup_parent(data);
		free_tab(cmd->args);
		free_tab(cmds);
	}
	i = -1;
	while (++i < data->cmd_count)
		waitpid(0 , &status, 0);
	restore_fd(data);
	return (0);
}
