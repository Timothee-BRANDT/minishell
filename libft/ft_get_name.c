/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_name.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 14:34:56 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/22 13:28:56 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_get_name(char *str)
{
	int		i;
	char	*result;	

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '=')
		i++;
	result = malloc(sizeof(char *) * i);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
