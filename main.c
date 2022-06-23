/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:07:48 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/23 12:37:38 by tbrandt          ###   ########.fr       */
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
	data->export = env_to_list(env);
	while (1)
	{
		data->buffer = readline(">$ ");
		if (!check_quote(data->buffer))
		{
			ft_putstr_fd("error, quotes not closed.\n", 2);
			exit(EXIT_FAILURE);
		}
		data->cmd = get_word_in_list(data->buffer, data);
		ft_export(&data->cmd, data);
		ft_print_list(data->cmd);
		add_history(data->buffer);
		free(data->buffer);
		ft_free_list(&data->cmd);
		//system("leaks minishell");
	}
	free(data->buffer);
	//we are on the develop branch;
	return (0);
}
