/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:12:18 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/04 17:25:31 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_name(t_list **cmd, t_data *data)
{
	data->str = ft_strdup(((char *)(*cmd)->content));
	// printf("pointeur data->str: %p\n", data->str);
	// printf("pointeur cmd->content: %p\n", (char *)(*cmd)->content);
	if (is_token(data->str))
		return (on_error("syntax error near unexpected token `newline'\n", 1));
	if (ft_strcmp(data->str, "=") == 0)
		return (on_error("not a valid identifier.\n", 1));
	init_data(data);
	if (set_export_var(data) == 1)
		return (on_error("Not a valid identifier.\n", 1));
	exec_export(data);
	if ((*cmd)->next != NULL && \
	!is_token((char *)(*cmd)->next->content))
		return (export_name(&(*cmd)->next, data));
	return (0);
}

void	exec_export(t_data *data)
{
	if (data->check == 1)
	{
		if (!is_in_list(&data->export, data->get_key))
			ft_lstadd_back(&data->export, ft_lstnew(ft_strdup(data->str)));
		if (!is_in_list(&data->env, data->get_key))
			ft_lstadd_back(&data->env, ft_lstnew(ft_strdup(data->str)));
		if (is_in_list(&data->export, data->get_key) && data->plus == 0)
			found_and_replace(&data->export, data->str);
		if (is_in_list(&data->export, data->get_key) && data->plus == 1)
			found_and_add(&data->export, data->str, data);
		if (is_in_list(&data->env, data->get_key) && data->plus == 0)
			found_and_replace(&data->env, data->str);
		if (is_in_list(&data->env, data->get_key) && data->plus == 1)
			found_and_add(&data->env, data->str, data);
	}
	else
	{
		if (!is_in_list(&data->export, data->get_key))
			ft_lstadd_back(&data->export, ft_lstnew(ft_strdup(data->str)));
	}
	free(data->get_key);
	free(data->str);
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
		if ((*cmd)->next && ft_strncmp((char *) \
		(ptr->next->content), (*cmd)->next->content, len) == 0)
		{
			tmp = ptr->next;
			ptr->next = ptr->next->next;
			free(tmp);
			if (!ptr->next)
				return ;
		}
		ptr = ptr->next;
	}
	if ((*cmd)->next && (*cmd)->next->next \
	&& !is_token((char *)(*cmd)->next->content))
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
		if ((*cmd)->next && ft_strncmp((char *) \
		(ptr->next->content), (*cmd)->next->content, len) == 0)
		{
			tmp = ptr->next;
			ptr->next = ptr->next->next;
			free(tmp);
			if (!ptr->next)
				return ;
		}
		ptr = ptr->next;
	}
	if ((*cmd)->next && (*cmd)->next->next && \
	!is_token((char *)(*cmd)->next->content))
		return (unset_name_export(export, &(*cmd)->next));
}
