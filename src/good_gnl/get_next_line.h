/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissat <maissat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:58:05 by maissat           #+#    #+#             */
/*   Updated: 2024/10/21 19:58:09 by maissat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE

#  define BUFFER_SIZE 5

# endif

char	*read_to_stash(int fd, char *stash);
char	*update_stash(char *stash, char *buffer);
char	*ft_strjoin(char *src, char *add);
int		ft_search(char	*str, char c);
char	*takeright(char	*str);
char	*takeleft(char	*str);
int		ft_strlen(char	*str);
char	*get_next_line(int fd);

#endif
