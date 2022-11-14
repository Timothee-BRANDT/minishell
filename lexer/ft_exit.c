/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmatthie <mmatthie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 11:24:53 by mmatthie          #+#    #+#             */
/*   Updated: 2022/11/14 14:58:20 by mmatthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**ft_lst2dpt(t_list	*lst)
{
	int	i;
	char	**tab;

	i = 0;
	tab = malloc(sizeof(char	*) * (ft_lstsize(lst) + 1));
	if (!tab)
		return (NULL);
	while (lst->content && lst->next)
	{
		tab[i] = ft_strdup(lst->content);
		i++;
		lst = lst->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	required_num_arg()
{
	ft_putstr_fd("Shell: exit: numeric argument required", 2);
	exit (255);
}

static int	check_content(char	*str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
	}
	if (str && str[i] && ft_isdigit(str[i]) == 0)
		return (1);
	return (0);
}

static long long check_arg(t_list	*lst)
{
	char	**tab;
	int		i;

	i = 1;
	tab = ft_lst2dpt(lst);
	while (tab && tab[i] && check_content(tab[i]) == 1)
		i++;
	printf("%d\n", check_content(tab[i]));
	if (tab && tab[i] && check_content(tab[i]) == 0)
		required_num_arg();
	ft_putstr_fd("Shell: exit: too many arguments", 2);
	return(1);
}

static long long	get_exit_nb(t_list	*lst)
{
	long long res;

	res = ft_atoll(lst->content);
	if (ft_atoll(lst->content))
	{
		res = res % 256;
		return(res);
	}
	else
	{
		ft_putstr_fd("Shell: exit: numeric argument required", 2);
		return(255);
	}
}


void	ft_exit(t_list	*lst, t_data	*data)
{
	long long		ex;
	(void) data;

	ex = 0;
	write(2, "exit\n", 5);
	if (ft_lstsize(lst) > 2)
		ex = check_arg(lst->next);
	else if (ft_lstsize(lst) == 1)
		exit(EXIT_SUCCESS);
	else if (ft_lstsize(lst) == 2)
	{
		ex = get_exit_nb(lst->next);
		if (ex)
			exit (ex);
		else
			required_num_arg();
	}
}
