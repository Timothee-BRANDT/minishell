/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <tbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 15:20:28 by tbrandt           #+#    #+#             */
/*   Updated: 2022/09/22 11:12:25 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    exec_command(t_list **cmd, t_data *data)
{
    char    **paths;
    char    **cmds;
    char    *good_cmd;

    paths = get_all_path(data);
    /*int i = 0;
    while(paths[i])
    {
        printf("paths:%s\n", paths[i]);
        i++;
    }
    i = 0;*/
    cmds = list_to_tab(*cmd);
    /*while(cmds[i])
    {
        printf("cmds :%s\n", cmds[i]);
        i++;
    }*/
    good_cmd = get_correct_cmd(paths, cmds);
    printf("%s\n", good_cmd);
}
