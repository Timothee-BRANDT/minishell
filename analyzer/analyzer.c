/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:42:43 by tbrandt           #+#    #+#             */
/*   Updated: 2022/09/22 10:58:30 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	built_in_analyzer(t_list **cmd, t_data	*data)
{
	if (!(*cmd))
		return ;
    if (is_built_in((char *)(*cmd)->content))
    {
		if (ft_strcmp((char *)(*cmd)->content, "env") == 0)
			ft_print_env(data->env);
		if (ft_strcmp((char *)(data->cmd)->content, \
		"export") == 0 && !data->cmd->next)
			ft_print_env(data->export);
		if (ft_strcmp((char *)(*cmd)->content, "export") == 0 && data->cmd->next)
			export_name(cmd, data, 0);
		if (ft_strcmp((char *)(*cmd)->content, "unset") == 0 && (*cmd)->next)
    	{
    		unset_name_export(&data->export, cmd);
    		unset_name_env(&data->env, cmd);
		}
	}
    else
		exec_command(cmd, data);
}

void	analyzer(t_list **cmd, t_data *data)
{
    built_in_analyzer(cmd, data);
}