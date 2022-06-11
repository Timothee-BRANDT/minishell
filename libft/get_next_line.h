/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrandt <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:20:19 by tbrandt           #+#    #+#             */
/*   Updated: 2022/02/13 19:31:02 by tbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include	<stdlib.h> // malloc
# include	<unistd.h>	// read
# include	<sys/types.h> // open
# include	<sys/stat.h> // open
# include	<fcntl.h> // open

char	*get_next_line(int fd);
int		ft_strchr(char *s, int c);
char	*ft_strdup(char *s);
char	*ft_strndup(char *s, int n);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);

#endif
