/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:07:48 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/22 13:14:39 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		data->buffer = readline("Bibishell>$ ");
		if (!check_quote(data->buffer))
		{
			ft_putstr_fd("Error, quotes not closed.\n", 2);
		    add_history(data->buffer);
		    //free(data->buffer);
		    ft_free_list(data->list);
            continue ;
		}
		data->list = get_word_in_list(data->buffer, data);
		analyzer(data, cmd);
		add_history(data->buffer);
		free(data->buffer);
		ft_lstclear(&data->list, &free_list);
		data->reset_prompt++;
		system("lsof -w -c minishell");
		//system("leaks minishell");
	}
	free(data->buffer);
	return (0);
}