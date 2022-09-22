/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:22:43 by tbrandt           #+#    #+#             */
/*   Updated: 2022/09/22 10:21:55 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    **list_to_tab(t_list *cmd)
{
	t_list *tmp;
    char	**tab;
	int		i;

	tmp = cmd;
	tab = malloc(sizeof(char *) * ft_lstsize(cmd) + 1);
	i = 0;
	while (tmp && !is_built_in((char *)cmd->content) && !is_token((char *)cmd->content))
	{
		tab[i] = malloc(sizeof(char) * ft_strlen((char *)tmp->content) + 1);
		tab[i] = (char *)tmp->content;
		printf("%s\n", tab[i]);
		cmd = cmd->next;
		tmp = cmd;
		i++;
	}
	return (tab);
}

char	**get_all_path(t_data *data)
{
	char    **result;
    t_list  *tmp;

    tmp = data->env;
	while (tmp->next != NULL && ft_strncmp((char *)tmp->content, "PATH=", 5) != 0)
    {
        data->env = data->env->next;
        tmp = data->env;
    }
	result = ft_split((char *)tmp->content + 5, ':');
    /*int i = 0;
    while(result[i])
    {
        printf("%s\n", result[i]);
        i++;
    }*/
	list_to_tab(data->cmd);
	return (result);
}

char    *get_correct_cmd(char **path, t_list *cmd)
{
   	char	*cmd_path;
	int		i;

	i = 0;
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], (char *)cmd->content);
		if (!access(cmd_path, F_OK | X_OK))
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL); 
}