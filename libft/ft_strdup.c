/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:56:12 by tbrandt           #+#    #+#             */
/*   Updated: 2021/11/02 18:36:19 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*ptr;
	int		i;

	ptr = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!ptr || !str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

/*
#include<stdio.h>
int main()
{
	char *str = "Cette chaine vient d'etre DUP";

	printf("Result: %s\n", ft_strdup(str));
}*/
