/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:50:38 by root              #+#    #+#             */
/*   Updated: 2025/04/22 19:37:28 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include "good_gnl/get_next_line.h" 

typedef struct s_map
{
	int	height;
	int	width;
	char	*name;
	char 	**tab;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color[3];
	int		ceiling_color[3];
}	t_map;

//UTILS
void	create_tab(t_map *map);
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
int		ft_strlcmp(char *s1, char *s2);
void	*ft_memset(void *b, int c, size_t len);
char 	*ft_strdup(char *str);
char 	*ft_strduptab(char *str, t_map *map);
void	show_tab(char **tab);
int		get_height(char *map_name, t_map *map);
int		ft_strncmp(char *s1, char *s2, int n );
char 	*ft_strduptext(char *str);
char 	*skip_spaces(char *str);
int		is_numeric(char c);
int 	str_in_str(char *str, char *to_find);
int		space_before(char *line);
char 	*ft_substr(char *str, int start, int end);
int		ft_atoi(char *str);
void	show_int_tab(int *tab);
void	show_struct_map(t_map map);

//CHECKERS

int	check_chars(t_map map);
int	check_name(char *str);
int	check_map(char *map_name, t_map *map);
int	check_borders(t_map map);

#endif