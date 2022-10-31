/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:11:49 by tbrandt           #+#    #+#             */
/*   Updated: 2022/10/31 14:12:17 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_option(char *tab)
{
	int	i;

	i = 0;
	if (tab && tab[0] == '-' && tab[1] == 'n')
	{
		i = 2;
		while (tab && tab[i])
		{
			if (tab[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

char	*ft_strjoin_echo_v2(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin_echo(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = ' ';
	str[i + 1] = '\0';
	return (str);
}

void	start_echo(char **cmds)
{
	int		i;
	char	*result;

	i = 1;
	while (check_option(cmds[++i]));
	result = NULL;
	if (!check_option(cmds[1]))
		result = ft_strjoin_echo(result, cmds[1]);
	while (cmds[i])
	{
		if (cmds && !cmds[i + 1] && !check_option(cmds[i]))
			result = ft_strjoin_echo_v2(result, cmds[i]);
		else 
			result = ft_strjoin_echo(result, cmds[i]);
		i++;
	}
	if (check_option(cmds[1]))
		ft_putstr(result);
	else
	{
		ft_putstr(result);
		write(1, "\n", 1);
	}
	free(result);
}
