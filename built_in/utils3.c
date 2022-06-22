/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:26:03 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/22 16:24:19 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	on_error(char *str, int code)
{
	write(1, str, ft_strlen(str));
	return (code);
}

void	free_two_string(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

void	init_data(t_data *data)
{
	data->i = 0;
	data->check = 0;
	data->plus = 0;
	data->get_key = ft_get_key(data->str);
}

int	set_export_var(t_data *data)
{
	while (data->str[data->i])
	{
		if (!ft_isalpha(data->str[data->i]))
			return (1);
		if (data->str[data->i] == '+' && data->str[data->i - 1] == '+')
			return (1);
		if (data->str[data->i] == '=')
		{
			data->check = 1;
			if (data->str[data->i - 1] == '+')
			{
				data->plus = 1;
				if (data->str[data->i - 2] == '+')
					return (1);
			}
		}
		data->i++;
	}
	return (0);
}

void	exec_add(t_data *data, char *str)
{
	char	*string;

	string = ft_strjoin_export(data->get_key_export, data->get_key_name);
	free_two_string(data->get_key_export, data->get_key_name);
	data->result = ft_strjoin(string, str);
	ft_manage(data->result);
	free(string);
}
