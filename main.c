/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:07:48 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/14 16:42:20 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_glo()
{
	g_glo.g_prompt = 0;
	g_glo.ctrl = 0;
	g_glo.g_signum = set_sig(g_glo.g_signum);
}

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
		set_glo();
		tty_hide_ctrl();
		data->buffer = readline("Bibishell>$ ");
		g_glo.g_prompt = 1;
		tty_show_ctrl();
		if (data->buffer == NULL)
			stop_handler(g_glo.g_signum);
		data->buffer_save = ft_strdup(data->buffer);
		if (!check_quote(data->buffer))
		{
			ft_putstr_fd("Error, quotes not closed.\n", 2);
		    add_history(data->buffer);
		    free(data->buffer);
			free_it(data->buffer_save);
            continue ;
		}
		data->buffer = ft_add_space(data->buffer, data);
		data->list = get_word_in_list(data->buffer, data);
		analyzer(data, cmd);
		add_history(data->buffer_save);
		free(data->buffer);
		free_it(data->buffer_save);
		ft_lstclear(&data->list, &free_list);
	}
	free(data->buffer);
	return (g_glo.g_signum);
}
