/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminos.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 10:25:25 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/14 10:25:26 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_usr_tty_config(t_var *var)
{
	tcgetattr(STDIN_FILENO, &var->usr_tty_config);
}

void	reset_usr_tty_config(t_var *var)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &var->usr_tty_config);
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
