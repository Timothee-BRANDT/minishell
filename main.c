/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:07:48 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/14 16:50:48 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *env[])
{
	t_data	*data;
	t_list	*cmd;
	int	i;

	i = 0;
	(void)argv;
	data = malloc(sizeof(t_data));
	cmd = malloc(sizeof(t_list));
	cmd->next = malloc(sizeof(t_list));
	cmd->content = (char *)"unset";
	cmd->next->content = (char *)"PAGER";
	printf("%s\n", (char *)(cmd->content));
	printf("%s\n", (char *)(cmd->next->content));
	// need to init_data
	if (argc == 1)
	{
		data->env = env_to_list(env);
		while(1)
		{
			data->buffer = readline(">$ ");
			if (check_quote(data) == 0)
				return(on_error("Quote not closed", 0));
			if (ft_strcmp(data->buffer, "env") == 0) // parsing de manu -> si le maillon = env;
				ft_print_env(data->env);
			if (ft_strcmp(data->buffer, "unset PAGER") == 0)
				unset_name(&data->env, cmd->next->content);
			//cmd = create_list(data);
			//ft_print_list(data);
			add_history(data->buffer);
		}
	}
	free(data->buffer);
	return (0);
}
