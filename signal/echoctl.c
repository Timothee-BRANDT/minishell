/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echoctl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:46:21 by mmatthie          #+#    #+#             */
/*   Updated: 2022/11/16 14:30:36 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_split(char	**to_split)
{
	int	i;

	i = 0;
	while (i >= 0)
	{
		free(to_split[i]);
		to_split[i] = 0;
		i--;
	}
	free (to_split);
}

void	tty_hide_ctrl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	tty_show_ctrl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}
