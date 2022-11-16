/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:55:22 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/16 14:23:00 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_key(char *str)
{
	int		i;
	char	*result;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	result = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_get_value(char *str)
{
	int		i;
	int		j;
	char	*result;

	if (!str)
		return (NULL);
	j = ft_strlen(str);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	result = malloc(sizeof(char) * ((j - i) + 1));
	j = 0;
	i++;
	while (str[i])
	{
		result[j] = str[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

int	is_token(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (str[0] == '<' && str[1] == '<')
			return (1);
		else if (str[0] == '>' && str[1] == '>')
			return (1);
		else if (str[0] == '<')
			return (1);
		else if (str[0] == '>')
			return (1);
		else if (str[0] == '|')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_export(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i++] = '=';
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

void	ft_print_env(t_list	*lst)
{
	if (!lst)
		return ;
	while (lst)
	{
		printf("declare -x %s\n", (char *)(lst->content));
		lst = lst->next;
	}
}
