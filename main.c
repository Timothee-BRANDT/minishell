/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 14:07:48 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/10 18:01:52 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char *buffer = NULL;
	char **buffer_splited;
	t_list *cmd;
	int	i;

	i = 0;
	while(1)
	{
		buffer = readline(">$ ");
		printf("buffer:%s\n", buffer);
		buffer_splited = ft_split(buffer, ' ');
		cmd = create_list(buffer_splited);
		ft_print_list(cmd);
		add_history(buffer);
	}
	free(buffer);
	return (0);
}
