/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 09:55:00 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/01 16:30:27 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	redirect_in(t_data *data)
{
	int	fd_in;
	int	tmp_in;
	int	tmp_out;

	tmp_in = dup(0);
	tmp_out = dup(1);
	if (data->infile)
	{
		fd_in = open(data->infile, O_RDONLY);
	}
	else
		fd_in = dup(tmp_in);
	dup2(0, fd_in);
	printf("let's do the in redirection\n");
	return (0);
}

/*void	redirect_out(t_data *data)
{
	printf("let's do the out redirection\n");
}

void	redirect_in_delim(t_data *data)
{
	printf("let's do the in_delimitor redirection\n");
}

void	redirect_out_append(t_data *data)
{
	printf("let's do the out_append redirection\n");
}*/