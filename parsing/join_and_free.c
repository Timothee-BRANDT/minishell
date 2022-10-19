#include "../minishell.h"


void	ft_free_list(t_list	**lst)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

int	get_join(char	*str, int count, t_data	*data)
{
	if (str && str[count])
	{
		check_token(str, count, data);
		if (data->token == '"' || data->token == '\'')
			count = get_second_with_token(str, count, data);
		else
			count = get_second_without_token(str, count, data);
		//ft_manage(data->join);
		//ft_manage(data->first);
		//free(data->first);
		while (str[count] && str[count] != ' ')
		{
			data->first = ft_strdup(data->get_word);
			free(data->get_word);
			//ft_manage(data->first);
			check_token(str, count, data);
			if (str[count] == data->token)
				data->indicate += 1;
			if (data->token == '"' || data->token == '\'')
				count = get_second_with_token(str, count, data);
			else
				count = get_second_without_token(str, count, data);
		}
	}
	return (count);
}

char	*ft_join_free_ss(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (!s1)
	{
		s1 = ft_calloc(1, 1);
		if (!s1)
			return (NULL);
	}
	if (!s2)
		return (NULL);
	join = malloc(sizeof(char) * ((int)ft_strlen(s1) + (int)ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	i = -1;
	while (s1[++i])
		join[i] = s1[i];
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = '\0';
	free(s1);
	free(s2);
	return (join);
}

char	*ft_join_free_s1(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (!s1)
	{
		s1 = ft_calloc(1, 1);
		if (!s1)
			return (NULL);
	}
	if (!s2)
		return (NULL);
	join = malloc(sizeof(char) * ((int)ft_strlen(s1) + (int)ft_strlen(s2)) + 1);
	if (!join)
		return (NULL);
	i = -1;
	while (s1[++i])
		join[i] = s1[i];
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = '\0';
	free(s1);
	return (join);
}

char	*ft_join_free_s2(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (!s1)
	{
		s1 = ft_calloc(1, 1);
		if (!s1)
			return (NULL);
	}
	if (!s2)
		return (NULL);
	join = malloc(sizeof(char) * ((int)ft_strlen(s1) + (int)ft_strlen(s2)) + 1);
	if (!join)
		return (NULL);
	i = -1;
	while (s1[++i])
		join[i] = s1[i];
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = '\0';
	free(s2);
	return (join);
}
