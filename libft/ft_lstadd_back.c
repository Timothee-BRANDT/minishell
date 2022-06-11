/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:49:23 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/10 17:04:08 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*p;

	if (!*alst)
	{
		*alst = new;
		return ;
	}
	p = ft_lstlast(*alst);
	p->next = new;
}
