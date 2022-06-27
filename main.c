/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:07:48 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/27 11:20:17 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char	**av, char	**env)
{
	t_data	*data;
	char	*cmd_history;

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
		cmd_history = ft_strdup(data->buffer);
		data->buffer = ft_add_space(data->buffer, data);
		data->cmd = get_word_in_list(data->buffer, data);
		ft_export(&data->cmd, data);
		ft_print_list(data->cmd);
		add_history(cmd_history);
		free (cmd_history);
		free (data->buffer);
		ft_free_list(&data->cmd);
		system("leaks minishell");
	}
	free(data->buffer);
	return (0);
}
