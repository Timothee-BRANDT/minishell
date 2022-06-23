#include "../minishell.h"

int	get_expend(char	*str, int count, t_data	*data)
{
	int	tmp;
	int	i;

	tmp = count;
	if (str[tmp] == '$')
	{
		if (str[tmp + 1] == '$')
			return (get_double(str, count, data));
		i = 0;
		while (str[++tmp] != '\'' && str[tmp] != '"' && str[tmp])
			i++;
		data->get_str_env = ft_calloc(1, i);
		data->get_str_env = ft_strncpy(data->get_str_env, &str[count + 1], i);
		data->get_env = getenv(data->get_str_env);
		if (data->get_env)
		{
			data->get_word = ft_calloc(1, ft_strlen(data->get_env));
			data->get_word = ft_strncpy(data->get_word, data->get_env, ft_strlen(data->get_env));
		}
		ft_manage(data->get_str_env);
		ft_manage(data->get_env);
		ft_manage(data->get_word);
		count = tmp;
		return (count);
	}
	return (count);
}

int	get_double(char	*str, int count, t_data	*data)
{
	data->first = ft_calloc(1, 5);
	data->first = ft_strdup("70591");
	data->get_word = ft_calloc(1, 5);
	data->get_word = ft_strncpy(data->get_word, data->first, 5);
	ft_manage(data->first);
	ft_manage(data->get_word);
	count += 2;
	if (str[count] != '$' || str[count] != '\0')
		count = get_join(str, count, count, data);
	return (count);
}

