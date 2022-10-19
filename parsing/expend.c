#include "../minishell.h"

/*
	-> $PATH : /Users/mmatthie/...
	-> lol$PATH : lol/Users/mmatthie/...
	-> $PATHlol : NULL;
	-> lol"$PATH" : lol/Users/mmatthie/...
	-> lol'$PATH' : lol$PATH
	-> lol$"PATH" : lolPATH
	-> lol'PATH' : lolPATH
	-> lol$"PA"TH : lolPATH
*/

int	get_expend_without_first(char	*str,int count, t_data	*data)
{
	int	tmp;
	int	j;

	j = 0;
	tmp = 0;
	if (str && str[count])
	{
		while (str[count] == '$')
			count++;
		j = count;
		while ((str && str[count]) && (str[count] != '"' && str[count] != '\'') && (str[count] != '$' && str[count] != ' '))
		{
			tmp++;
			count++;
		}
		make_expend(str, j, tmp, data);
		if (str[count] != ' ' && str[count])
		{
			data->first = ft_strdup(data->get_word);
			free_it(data->get_word);
			count = get_join(str, count, data);
		}
	}
	return (count);
}

int	get_expend(char	*str, int j, int count, t_data	*data)
{
	int	tmp;

	tmp = 0;
	//count = j;
	if (str && str[j] && str[j] == '$')
	{
		while (str[j] == '$')
			j++;
		count = j;
		while ((str && str[j]) && (str[j] != '"' && str[j] != '\'') && (str[j] != ' ' && str[j] != '$'))
		{
			tmp++;
			j++;
		}
		count = make_expend(str, count, tmp, data);
		if (str[count] != ' ' && str[count])
		{
			data->first = ft_strdup(data->get_word);
			free(data->get_word);
			count = get_join(str, count, data);
		}
	}
	return (count);
}

int	first_expend(char	*str, int count, t_data	*data)
{
	int j;

	j = count;
	if (str[j] == '$')
		count = get_expend_without_first(str, j, data);
	if (str[count] != ' ' && str[count])
	{
		if ((str[count] == '\'' || str[count] == '"'))
			count = get_join(str, count, data);
	}
	return (count);
}


/*int	get_expend_with_token(char	*str, int j, int count, t_data	*data)
{
	int	tmp;

	tmp = 0;
	if (str[j] == '$')
	{
		while (str[j] == '$')
			j++;
		count = j;
		while ((str[j] != data->token) && str[j])
		{
			tmp++;
			j++;
		}
		if (str[j] == data->token)
			count = make_expend(str, count, tmp, data);
		else if ((str[j] == '\'' || str[j] == '"') && str[j])
			count = get_join(str, j, data);
	}
	return (count);
}*/


int	make_expend(char	*str, int	j, int content, t_data	*data)
{
	char	*expend;
	int		count;

	count = content + j;
	expend = ft_substr(str, j, content);
	data->expend = get_env(expend, data->export);
	expend_it(data, str, j);
	free(data->expend);
	return (count);
}

void	little_one(t_data	*data)
{
	data->get_word = ft_calloc(1, 1);
	data->get_word[0] = '\0';
}

void expend_it(t_data	*data, char	*str, int j)
{
	if (str[j - 2] && str[j - 2] != ' ' && (data->token == 0 || data->token == '"'))
	{
		if (data->expend && data->expend[0])
			data->get_word = ft_join_free_s1(data->first, data->expend);
		else
		{
			data->get_word = ft_strdup(data->first);
			free(data->first);
		}
	}
	else
	{
		if (data->expend && data->expend[0])
			data->get_word = ft_strdup(data->expend);
		else
			little_one(data);
	}
}

char	*get_env(char *key, t_list *export)
{
	t_list	*tmp;
	int		len;
	char	*tab;

	tab = NULL;
	tmp = export;
	len = ft_strlen(key);
	if (key && key[0])
	{
		if (!ft_strncmp((char *)tmp->content, key, len))
		{
			tab = ft_get_value((char *)tmp->content);
			free(key);
			return (tab);
		}
		while (tmp->next)
		{
			if (!ft_strncmp((char *)tmp->next->content, key, len))
			{
				tab = ft_get_value((char *)tmp->next->content);
				free(key);
				return (tab);
			}
			tmp = tmp->next;
		}
		free(key);
	}
	return (NULL);
}
