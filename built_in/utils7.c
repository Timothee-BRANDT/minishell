/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 14:07:48 by tbrandt           #+#    #+#             */
/*   Updated: 2022/11/07 23:42:51 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int is_export(char **tab, t_data *data)
{
    t_list *list;

    if (tab[0] && !ft_strcmp(tab[0], "export"))
    {
	    if  (!tab[1])
        {
            ft_print_env(data->export);
            return (1);
        }
	    else if (ft_strlen2d(tab) > 1)
    	{
	    	list = dpt_to_lst_export(tab);
		    export_name(&list, data);
		    ft_lstclear(&list, free);
            return (1);
    	}
    }
	return (0);
}

int is_unset(char **tab, t_data *data)
{
    t_list *list;
    
    if (tab[0] && !ft_strcmp(tab[0], "unset"))
	{
		if (!tab[1])
			return (1);
		list = dpt_to_lst_env(tab);
		unset_name_env(&data->env, &list);
		unset_name_export(&data->export, &list);
		ft_lstclear(&list, free);
		return (1);
	}
    return (0);
}