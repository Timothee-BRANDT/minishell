/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 16:34:44 by mmatthie          #+#    #+#             */
/*   Updated: 2022/10/19 11:02:29 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char	**av, char	**env)
{
	t_data	*data;

	(void) ac;
	(void) av;
	data = malloc(sizeof(t_data));
	data->env = env_to_list(env);
	//ft_print_list(data->env);
	data->export = env_to_list(env);
	while (1)
	{
		set_data(data);
		data->buffer = readline(">$ ");
		if (!check_quote(data->buffer))
		{
			ft_putstr_fd("error, quotes not closed.\n", 2);
			exit(EXIT_FAILURE);
		}
		data->buffer = ft_add_space(data->buffer, data);
		data->cmd = get_word_in_list(data->buffer, data);
		ft_export(&data->cmd, data);
		ft_print_list(data->cmd);
		add_history(data->buffer);
		free(data->buffer);
		ft_free_list(&data->cmd);
		//system("leaks minishell");
	}
	free(data->buffer);
	return (0);
}
