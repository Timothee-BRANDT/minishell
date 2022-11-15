/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echoctl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:46:21 by mmatthie          #+#    #+#             */
/*   Updated: 2022/11/15 16:39:10 by tbrandt          ###   ########.fr       */
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

void	set_tty(t_data	*data, char	**env)
{
	char	**args;
	pid_t	pid;

	(void)data;
	args = ft_split("/bin/stty echoctl", ' ');
	pid = fork();
	if (pid == -1)
	{
		write(2, "error in stty echoctl\n", 22);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve("/bin/stty", args, env) == -1)
		{
			write(2, "error in execve\n", 16);
			exit(EXIT_FAILURE);
		}
	}
	ft_free_split(args);
}

void	unset_tty(t_data	*data, char	**env)
{
	char	**args;
	pid_t	pid;

	(void)data;
	args = ft_split("/bin/stty -echoctl", ' ');
	pid = fork();
	if (pid == -1)
	{
		write(2, "error in stty -echoctl\n", 22);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve("/bin/stty", args, env) == -1)
		{
			write(2, "error in execve\n", 16);
			exit(EXIT_FAILURE);
		}
	}
	ft_free_split(args);
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
