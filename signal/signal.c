/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:39:23 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/15 16:40:18 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_sig(int sig)
{
	struct sigaction	sa;

	sa.sa_handler = ctrl_c;
	sigaction(SIGINT, &sa, NULL);
	return (sig);
}

void	ctrl_c(int sig)
{
	(void)sig;
	if (g_glo.g_prompt == 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_glo.g_signum = 1;
	}
	else
		g_glo.g_prompt = 0;
}

void	stop_handler(int sig)
{
	(void)sig;
	write(2, "exit\n", 5);
	exit(EXIT_SUCCESS);
}
