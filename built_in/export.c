/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:12:18 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/21 19:13:46 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_data(t_data *data)
{
	data->i = 0;
	data->check = 0;
	data->plus = 0;
	data->get_key = ft_get_key(data->str);
}

void	set_export_var(t_data *data)
{
	while (data->str[data->i])
	{
		if (data->str[data->i] == '=')
		{
			data->check = 1;
			if (data->str[data->i - 1] == '+')
				data->plus = 1;
		}
		data->i++;
	}
}

int	export_name(t_list **cmd, t_data *data, int code)
{
	t_list	*tmp;

	tmp = *cmd;
	if (code == 0)
		tmp = (*cmd)->next;
	data->str = ((char *)tmp->content);
	data->removed = remove_plus(data->str);
	init_data(data);
	if (is_token(data->str))
		return (2);
	if (ft_strcmp(data->str, "=") == 0)
		return (3);
	if (code == 0)
		set_export_var(data);
	exec_export(data);
	if ((*cmd)->next != NULL && \
	!is_token((char *)(*cmd)->next->content))
		return (export_name(&(*cmd)->next, data, 1));
	return (0);
}

void	exec_export(t_data *data)
{
	if (data->check == 1)
	{
		if (is_in_list(&data->export, data->get_key) == 1)
		{
			if (data->plus == 0)
				found_and_replace(&data->export, data->str);
			else
			{
				data->check = 0;
				found_and_add(&data->export, data->str, data);
				if (is_in_list(&data->env, data->get_key) == 1)
					found_and_add(&data->env, data->str, data);
			}
		}
		else
			ft_lstadd_back(&data->export, ft_lstnew(data->str));
		if (is_in_list(&data->env, data->get_key) == 1 && data->check == 1)
				found_and_replace(&data->env, data->str);
		if (is_in_list(&data->env, data->get_key) == 0)
			ft_lstadd_back(&data->env, ft_lstnew(data->str));
	}
	else if (is_in_list(&data->export, data->get_key) == 0)
		ft_lstadd_back(&data->export, ft_lstnew(data->str));
	free(data->get_key);
	free(data->removed);
}

void	unset_name_env(t_list **env, t_list **cmd)
{
	t_list	*ptr;
	t_list	*tmp;
	int		len;

	ptr = *env;
	len = ft_strlen((char *)(*cmd)->next->content);
	while (ptr->next != NULL)
	{
		if ((*cmd)->next && ft_strncmp((char *)(ptr->next->content), (*cmd)->next->content, len) == 0)
		{
			tmp = ptr->next;
			ptr->next = ptr->next->next;
			free(tmp);
			if (!ptr->next)
				return ;
		}
		ptr = ptr->next;
	}
	if ((*cmd)->next && (*cmd)->next->next && !is_token((char *)(*cmd)->next->content))
		return (unset_name_export(env, &(*cmd)->next));
}

void	unset_name_export(t_list **export, t_list **cmd)
{
	t_list	*ptr;
	t_list	*tmp;
	int		len;

	ptr = *export;
	len = ft_strlen((char *)(*cmd)->next->content);
	while (ptr->next != NULL)
	{
		if ((*cmd)->next && ft_strncmp((char *)(ptr->next->content), (*cmd)->next->content, len) == 0)
		{
			tmp = ptr->next;
			ptr->next = ptr->next->next;
			free(tmp);
			if (!ptr->next)
				return ;
		}
		ptr = ptr->next;
	}
	if ((*cmd)->next && (*cmd)->next->next && !is_token((char *)(*cmd)->next->content))
		return (unset_name_export(export, &(*cmd)->next));
}

void	ft_export(t_list **cmd, t_data	*data)
{
	//printf("(*cmd)->content :%s\n", (char *)(*cmd)->content);
	if (ft_strcmp((char *)(*cmd)->content, "env") == 0)
		ft_print_env(data->env);
	if (ft_strcmp((char *)(data->cmd)->content, "export") == 0 && !data->cmd->next)
		ft_print_env(data->export);
	if (data->cmd->next)
		export_name(cmd, data, 0);
	//printf("(*cmd)->content :%s\n", (char *)(*cmd)->content);
	if (ft_strcmp((char *)(*cmd)->content, "unset") == 0 && (*cmd)->next)
	{
		unset_name_export(&data->export, cmd);
		unset_name_env(&data->env, cmd);
	}
}
