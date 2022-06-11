/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:26:57 by tbrandt           #+#    #+#             */
/*   Updated: 2021/10/29 14:23:35 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*t;
	int		len;

	if (!lst)
		return (0);
	len = 1;
	t = lst->next;
	while (t != NULL)
	{
		t = t->next;
		len++;
	}
	return (len);
}
