/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:37:52 by tbrandt           #+#    #+#             */
/*   Updated: 2022/06/10 17:09:14 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void  *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->prev = NULL;
	list->next = NULL;
	return (list);
}
/*
#include <stdio.h>
int main()
{
	t_list *p;

	p = ft_lstnew((void *)53453453);
	printf("%d", (int)p->content);
}*/
