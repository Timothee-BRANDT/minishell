/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:07:48 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/04 17:34:49 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int global_signum = 0;

int	main(int ac, char	**av, char	**env)
{
	t_data	*data;
	t_cmd	*cmd;

	(void) ac;
	(void) av;
	cmd = malloc(sizeof(t_cmd));
	data = malloc(sizeof(t_data));
	data->env = env_to_list(env);
	data->export = env_to_list(env);
	while (1)
	{
		set_data(data);
		data->buffer = readline("Bibishell>$ ");
		data->buffer_save = ft_strdup(data->buffer);
		if (!check_quote(data->buffer))
		{
			ft_putstr_fd("Error, quotes not closed.\n", 2);
		    add_history(data->buffer);
		    free(data->buffer);
            continue ;
		}
		data->buffer = ft_add_space(data->buffer, data);
		data->list = get_word_in_list(data->buffer, data);
		analyzer(data, cmd);
		add_history(data->buffer_save);
		free(data->buffer);
		free_it(data->buffer_save);
		ft_lstclear(&data->list, &free_list);
		// system("leaks minishell");
	}
	free(data->buffer);
	return (0);
}
