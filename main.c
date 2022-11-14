/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:07:48 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/14 11:09:58 by mmatthie         ###   ########.fr       */
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
		//unset_tty(data, env);
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
		    //free(data->buffer);
			continue ;
		}
		data->buffer = ft_add_space(data->buffer, data);
		data->list = get_word_in_list(data->buffer, data);
		//ft_print_list(data->list);
		if (!ft_strcmp("exit", data->list->content))
			ft_exit(data->list, data);
		ft_print_list(data->list);
		analyzer(data, cmd);
		//g_glo.g_prompt = 1;
		add_history(data->buffer_save);
		free(data->buffer);
		free_it(data->buffer_save);
		ft_lstclear(&data->list, &free_list);
		//system("leaks minishell");
		// system("lsof -w -c minishell");
	}
	free(data->buffer);
	return (g_glo.g_signum);
}
