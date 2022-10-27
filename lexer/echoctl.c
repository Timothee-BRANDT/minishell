/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echoctl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:46:21 by mmatthie          #+#    #+#             */
/*   Updated: 2022/10/27 15:19:44 by tbrandt          ###   ########.fr       */
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
	(void)data;
	char	*buffer;
	char	**path;
	pid_t	pid;

	buffer = ft_strdup("/bin/stty echoctl");
	path = ft_split(buffer, ' ');
	pid = fork();
	if (pid == -1)
	{
		write(2, "error in stty echoctl\n", 22);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(path[0], &path[0], env) == -1)
		{
			write(2, "error in execve\n", 16);
			exit(EXIT_FAILURE);
		}
	}
	free_it(buffer);
	ft_free_split(path);
}

void	unset_tty(t_data	*data, char	**env)
{
	(void)data;
	char	*buffer;
	char	**path;
	pid_t	pid;

	buffer = ft_strdup("/bin/stty -echoctl");
	path = ft_split(buffer, ' ');
	pid = fork();
	if (pid == -1)
	{
		write(2, "error in stty -echoctl\n", 22);
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		if (execve(path[0], &path[0], env) == -1)
		{
			write(2, "error in execve\n", 16);
			exit(EXIT_FAILURE);
		}
	}
	ft_free_split(path);
	free_it(buffer);
}
