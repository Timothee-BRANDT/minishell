#include "../minishell.h"

int	export_name(t_list **env, t_list **export, t_list **cmd, int code)
{
	int	i;
	int	check;
	int plus;
	char *str;
	
	i = -1;
	
	check = 0;
	plus = 0;
	if (code == 0)
		*cmd = (*cmd)->next;	
	str = ((char *)(*cmd)->content);
	if (is_token(str))
		return (2);
	if (ft_strcmp(str, "=") == 0)
		return (3);
	while (str[++i])
	{
		if (str[i] == '=')
		{
			check = 1;
			if (str[i - 1] == '+')
				plus = 1;
		}
	}
	if (check == 1)
	{
		if (is_in_list(export, ft_get_key(str)) == 1)
		{
			if (plus == 0)
			{
				found_and_replace(export, str);
			}
			else
			{
				check = 0;
				found_and_add(export, str);
				if (is_in_list(env, ft_get_key(str)) == 1)
					found_and_add(env, str);
			}
		}
		else
			ft_lstadd_back(export, ft_lstnew(remove_plus(str)));
		if (is_in_list(env, ft_get_key(str)) == 1 && check == 1)
				found_and_replace(env, str);
		if (is_in_list(env, ft_get_key(str)) == 0)
			ft_lstadd_back(env, ft_lstnew(remove_plus(str)));
	}
	else if (is_in_list(export, ft_get_key(str)) == 0)
		ft_lstadd_back(export, ft_lstnew(remove_plus(str)));
	if ((*cmd)->next != NULL && !is_token((char *)(*cmd)->next->content))
		return (export_name(env, export, &(*cmd)->next, 1));
	return (0);
}

void	unset_name_env(t_list **env, char *name)
{
	t_list	*ptr;
	t_list	*tmp;
	int		len;

	ptr = *env;
	len = ft_strlen(name);
	while (ptr->next != NULL)
	{
		if (ft_strncmp((char *)(ptr->next->content), name, len) == 0)
		{
			tmp = ptr->next;
			ptr->next = ptr->next->next;
			free(tmp);
			if (!ptr->next)
				return ;
		}
		ptr = ptr->next;
	}
}

void	unset_name_export(t_list **export, char *name)
{
	t_list	*ptr;
	t_list	*tmp;
	int		len;

	ptr = *export;
	len = ft_strlen(name);
	while (ptr->next != NULL)
	{
		if (ft_strncmp((char *)(ptr->next->content), name, len) == 0)
		{
			tmp = ptr->next;
			ptr->next = ptr->next->next;
			free(tmp);
			if (!ptr->next)
				return ;
		}
		ptr = ptr->next;
	}
}

void	ft_export(t_data	*data, t_list	*cmd)
{
	if (ft_strcmp((char *)(cmd)->content, "env") == 0)
		ft_print_env(data->env);
	if (ft_strcmp((char *)(cmd)->content, "export") == 0 && !cmd->next)
		ft_print_env(data->export);
	else if (cmd->next)
		export_name(&data->env, &data->export, &cmd, 0);
}
