/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_and_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 00:26:33 by mmatthie          #+#    #+#             */
/*   Updated: 2022/11/09 17:45:10 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_list(t_list	**lst)
{
	t_list	*tmp;
	t_list	*tmp2;

	tmp = *lst;
	while (tmp)
	{
		tmp2 = tmp->next;
		free(tmp);
		tmp = tmp2;
	}
}

int	get_join(char	*str, int count, t_data	*data)
{
	if (str && str[count])
	{
		ft_manage(data->get_word);
		check_token(str, count, data);
		if (data->token == '"' || data->token == '\'')
			count = get_second_with_token(str, count, data);
		else
			count = get_second_without_token(str, count, data);
		ft_manage(data->get_word);
	}
	return (count);
}

char	*ft_join_free_ss(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (!s1)
	{
		s1 = ft_calloc(1, 1);
		if (!s1)
			return (NULL);
	}
	if (!s2)
		return (NULL);
	join = malloc(sizeof(char) * ((int)ft_strlen(s1) + (int)ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	i = -1;
	while (s1[++i])
		join[i] = s1[i];
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = '\0';
	free_it(s1);
	free_it(s2);
	return (join);
}

char	*ft_join_free_s1(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (!s1)
	{
		s1 = ft_calloc(1, 1);
		if (!s1)
			return (NULL);
	}
	if (!s2)
		return (NULL);
	join = malloc(sizeof(char) * ((int)ft_strlen(s1) + (int)ft_strlen(s2)) + 1);
	if (!join)
		return (NULL);
	i = -1;
	while (s1[++i])
		join[i] = s1[i];
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = '\0';
	free_it(s1);
	return (join);
}

char	*ft_join_free_s2(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*join;

	if (!s1)
	{
		s1 = ft_calloc(1, 1);
		if (!s1)
			return (NULL);
	}
	if (!s2)
		return (NULL);
	join = malloc(sizeof(char) * ((int)ft_strlen(s1) + (int)ft_strlen(s2)) + 1);
	if (!join)
		return (NULL);
	i = -1;
	while (s1[++i])
		join[i] = s1[i];
	j = 0;
	while (s2[j])
		join[i++] = s2[j++];
	join[i] = '\0';
	free_it(s2);
	return (join);
}
