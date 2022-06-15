/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:07:48 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/15 14:55:41 by tbrandt          ###   ########.fr       */
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
	cmd->next->content = (char *)"LESS";
	printf("%s\n", (char *)(cmd->content));
	printf("%s\n", (char *)(cmd->next->content));
	// need to init_data
	// export -> checker si je trouve un espace, si j'en trouve un, mettre cette variable dans export et pas dans env;
	if (argc == 1)
	{
		data->env = env_to_list(env);
		data->export = env_to_list(env);
		while(1)
		{
			data->buffer = readline(">$ ");
			if (check_quote(data) == 0)
				return(on_error("Quote not closed", 0));
			if (ft_strcmp(data->buffer, "env") == 0) // parsing de manu -> si le maillon = env;
				ft_print_env(data->env);
			if (ft_strcmp(data->buffer, "export") == 0) // parsing de manu -> si le maillon = env;
				ft_print_env(data->export);
			if (ft_strcmp(data->buffer, "export a=b") == 0)
			{
				export_name(&data->env, &data->export, "a=b");
			}
			if (ft_strcmp(data->buffer, "export a") == 0)
			{
				export_name(&data->env, &data->export, "a");
			}
			if (ft_strcmp(data->buffer, "export c") == 0)
			{
				if (export_name(&data->env, &data->export, "c") == 2)
					printf("%s\n", "export: `=': not a valid identifier");
			}
			if (ft_strcmp(data->buffer, "unset LESS") == 0)
			{
				unset_name_env(&data->env, cmd->next->content);
				unset_name_export(&data->export, cmd->next->content);
			}
			if (ft_strcmp(data->buffer, "unset a") == 0)
			{
				unset_name_env(&data->env, "a");
				unset_name_export(&data->export, "a");
			}
			if (ft_strcmp(data->buffer, "unset c") == 0)
			{
				unset_name_env(&data->env, "c");
				unset_name_export(&data->export, "c");
			}
			//cmd = create_list(data);
			//ft_print_list(data);
			add_history(data->buffer);
		}
	}
	free(data->buffer);
	return (0);
}
