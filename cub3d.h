/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:50:38 by root              #+#    #+#             */
/*   Updated: 2025/05/04 15:52:06 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include "src/good_gnl/get_next_line.h"
#include "math.h"
#include "minilibx-linux/mlx.h"

# define WIDTH 1280
# define HEIGHT 720
# define W 119
# define A 97 	
# define S 115
# define D 100
# define PI 3.1415926535
# define ROT_LEFT 65361
# define ROT_RIGHT 65363
# define PLAYER_RADIUS 12.0f
# define ECHAP 65307

typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	int				size_line;
	int				bbp;
	int				endian;
	char			*data;
	struct s_player *player;
	struct s_map	*map;
} t_game;

typedef struct s_map
{
	int		height;
	int		width;
	char	*name;
	char 	**tab;
	struct s_player *player;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	char	orientation;
	int		floor_color[3];
	int		ceiling_color[3];
}	t_map;

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;
	int		key_up;
	int		key_down;
	int		key_left;
	int		key_right;
	int		left_rotate;
	int		right_rotate;
}	t_player;

// COLISION

int can_move(t_map *map, float x, float y);
int is_walkable(t_map *map, float x, float y);

// CHECK

int	check_all_textures(const t_map *map);
int		valid_path(const char *path);


//DRAW

void	draw_square(int x, int y, int color, int size, t_game *game);
int		draw_loop(t_game *game);

//PLAYER

void	init_player(t_player *player, t_map map);
int 	key_press(int keycode, t_player *player);
int 	key_release(int keycode, t_player *player);
void    move_player(t_player *player, t_map *map);

//RAYCASTING

void	init_game(t_game *game, t_map map);
void	put_pixel(int x, int y, int color, t_game *game);

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
char	*ft_strrchr(const char *s, int c);
int		close_window_cross(void);

//CHECKERS

int		check_chars(t_map *map);
int		check_name(char *str);
int		check_map(char *map_name, t_map *map);
int		check_borders(t_map map);
int		parse_texture(t_map *map);

#endif