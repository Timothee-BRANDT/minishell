/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:07:48 by tbrandt           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/06/23 17:08:12 by mmatthie         ###   ########.fr       */
=======
/*   Updated: 2022/10/27 16:21:03 by tbrandt          ###   ########.fr       */
>>>>>>> tim
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
	// printf("main\n");
	// ft_print_list(data->env);
	// printf("\n");
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
		    //free(data->buffer);
            continue ;
		}
		data->buffer = ft_add_space(data->buffer, data);
		data->list = get_word_in_list(data->buffer, data);
		ft_print_list(data->list);
		analyzer(data, cmd);
		add_history(data->buffer_save);
		free(data->buffer);
		free_it(data->buffer_save);
		ft_lstclear(&data->list, &free_list);
		// system("lsof -w -c minishell");
		//system("leaks minishell");
	}
	free(data->buffer);
	//we are on the develop branch;
	// this a feature made by the feature branch
	return (0);
}