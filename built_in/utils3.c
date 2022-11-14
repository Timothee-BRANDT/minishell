/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:26:03 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/14 13:52:20 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_error(char *infile, char *outfile)
{
	printf("Minishell: infile not found\n");
	free(infile);
	infile = NULL;
	free(outfile);
	outfile = NULL;
	return (0);
}

void	free_all(t_data *data)
{
	free(data->get_key_name);
	free(data->get_key_export);
	free(data->get_value_export);
	free(data->get_value_name);
	free(data->string);
	ft_manage(data->result);
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
