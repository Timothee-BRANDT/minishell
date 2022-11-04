/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:22:43 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/04 17:34:27 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_all_path(t_data *data)
{
	char    **result;
    t_list  *tmp;

    tmp = data->env;
	while (tmp->next != NULL && ft_strncmp_v2((char *)tmp->content, "PATH=", 5) != 0)
    {
        data->env = data->env->next;
        tmp = data->env;
    }
	result = ft_split((char *)tmp->content + 5, ':');
	return (result);
}

char    *get_correct_cmd(char **paths, char **cmds)
{
   	char	*cmd_path;
	int		i;

	i = 0;
	if (!access(cmds[0], F_OK | X_OK))
		return (cmds[0]);
	while (paths[i])
	{
		cmd_path = ft_strjoin_slash(paths[i], cmds[0]);
		if (!access(cmd_path, F_OK | X_OK))
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL); 
}