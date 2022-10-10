/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 11:23:18 by tbrandt           #+#    #+#             */
/*   Updated: 2022/09/28 10:01:36by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(char *key, t_list *env)
{
	t_list	*tmp;
	int		len;
	char	*tab;

	tmp = env;
	ft_print_list(env);
	len = ft_strlen(key);
	while (tmp)
	{
		if (!ft_strncmp((char *)tmp->content, key, len))
		{
			tab = ft_get_value((char *)tmp->content);
			return (tab);
		}
		tmp = tmp->next;
	}
	return (NULL);
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
    	list = list->next;
        tmp = list;
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

char	**extract_cmd(char **cmd, t_data *data)
{
	int	i;
	static	int	j = 0;
	char **final_cmd;

	final_cmd = malloc(sizeof(char *) * 500);
	i = 0;
	(void)data;
	while (cmd[j] && ft_strcmp(cmd[j], "|") != 0)
	{
		final_cmd[i] = ft_strdup(cmd[j]);
		i++;
		j++;
	}
	if (cmd[j] && ft_strcmp(cmd[j], "|") == 0)
		j++;
	final_cmd[i] = NULL;
	if(j == ft_strlen2d(cmd))
		ft_bzero(&j, sizeof(int));
	return (final_cmd);
}
