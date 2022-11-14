/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 18:07:44 by mmatthie          #+#    #+#             */
/*   Updated: 2022/11/04 18:10:11 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exit_code(int signum)
{
	if (WIFEXITED(signum))
		return (WEXITSTATUS(signum));
	else if (WIFSIGNALED(signum))
		return (WTERMSIG(signum) + 128);
	else if (WIFSTOPPED(signum))
		return (WTERMSIG(signum) + 128);
	return (0);
}
