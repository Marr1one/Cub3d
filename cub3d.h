/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:50:38 by root              #+#    #+#             */
/*   Updated: 2025/06/25 01:58:07 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "math.h"
# include "minilibx-linux/mlx.h"
# include "src/good_gnl/get_next_line.h"
# include <stdio.h>
# include <stdlib.h>

# define PLAYER_RADIUS 12.0f
# define WIDTH 1280
# define HEIGHT 720
# define W 119
# define A 97
# define S 115
# define D 100
# define PI 3.1415926535
# define ROT_LEFT 65361
# define ROT_RIGHT 65363
# define ECHAP 65307

typedef struct s_texture
{
	void			*img;
	char			*data;
	int				width;
	int				height;
	int				bpp;
	int				size_line;
	int				endian;
	int				tex_x;
	int				tex_y;
	int				lh;
}					t_texture;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	int				size_line;
	int				bbp;
	int				endian;
	char			*data;
	struct s_player	*player;
	struct s_map	*map;
	t_texture		*no;
	t_texture		*so;
	t_texture		*we;
	t_texture		*ea;
}					t_game;

typedef struct s_map
{
	int				height;
	int				width;
	char			*name;
	char			**tab;
	struct s_player	*player;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	char			orientation;
	int				floor_color[3];
	int				ceiling_color[3];
}					t_map;

typedef struct s_player
{
	float			x;
	float			y;
	float			angle;
	int				key_up;
	int				key_down;
	int				key_left;
	int				key_right;
	int				left_rotate;
	int				right_rotate;
	float			dx;
	float			dy;
}					t_player;

typedef struct s_ray
{
	float			ray_dir_x;
	float			ray_dir_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	float			side_dist_x;
	float			side_dist_y;
	float			delta_dist_x;
	float			delta_dist_y;
	int				side;
	float			raw_dist;
}					t_ray;

// COLORS

int				fill_rgb(char *str, int color_rgb[3]);
int				fill_color(t_map *map, char *str, char choice);
int				is_color_line(char *line);
int				parse_and_store_color(char *str, int *i, int *j, int rgb[3]);


// TEXTURES

t_texture			*load_texture(void *mlx, char *path);
void				init_textures(t_game *game, t_map *map);
void				draw_column_textured(t_player *player, t_game *game,
						float ray_angle, int x);
void				fill_texture(t_map *map, char *trimmed);
int					is_texture_line(char *line);
float				get_wall_x(t_ray *ray, t_player *pl);
float				get_perp_dist(t_ray *ray, t_player *pl, float angle);
t_texture			*choose_tex(t_game *g, t_ray *r);
int					get_tex_x(t_ray *r, t_texture *tex, float wall_x);
int					validate_texture_line_no_inner_spaces(char *line);

//MAP

int					map_after_all(t_map map);
int					check_invalid_lines(t_map map);

// COLISION

int					can_move(t_map *map, float x, float y);
int					is_walkable(t_map *map, float x, float y);

// CHECK

int					check_all_textures(const t_map *map);
int					valid_path(const char *path);
void				cleanup_remaining_lines(char **line, int fd);
int					process_color_lines(char **line, t_map *map, int fd);
void				process_texture_lines(char **line, t_map *map, int fd);

// DRAW

int					draw_loop(t_game *game);

// PLAYER

void				init_player(t_player *player, t_map map);
int					key_press(int keycode, t_player *player);
int					key_release(int keycode, t_player *player);
void				move_player(t_player *player, t_map *map);
void				rotate_player(t_player *player);
void				get_player_move_delta(t_player *player, float speed);

// RAYCASTING

void				init_game(t_game *game, t_map map);
void				put_pixel(int x, int y, int color, t_game *game);
int					dda_while_loop(t_ray *ray, t_game *game);
int					raycast_wall(t_player *player, t_game *game,
						float ray_angle, t_ray *ray);

// UTILS
void				create_tab(t_map *map);
int					is_space_line(char *line);
int					is_direction(char c);
int					ft_strlen(char *str);
int					ft_strcmp(char *s1, char *s2);
int					ft_strlcmp(char *s1, char *s2);
int					process_map_line(char *line, int *map_start, int *map_finish);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strdup(char *str);
char				*ft_strduptab(char *str, t_map *map);
void				show_tab(char **tab);
int					get_height(char *map_name, t_map *map);
int					ft_strncmp(char *s1, char *s2, int n);
char				*ft_strduptext(char *str);
char				*skip_spaces(char *str);
int					is_numeric(char c);
int					str_in_str(char *str, char *to_find);
int					space_before(char *line);
char				*ft_substr(char *str, int start, int end);
int					ft_atoi(char *str);
void				show_int_tab(int *tab);
void				show_struct_map(t_map map);
char				*ft_strrchr(const char *s, int c);
int					close_window_cross(t_game *game);
int					rgb_to_hex_int(int r, int g, int b);
int					ft_max(int a, int b);
void				consume_remaining_file(int fd);

// CHECKERS

int					count_color_line(t_map map);
int					count_tex_line(t_map map);
int					check_chars(t_map *map);
int					check_name(char *str);
int					check_map(char *map_name, t_map *map);
int					check_borders(t_map map);
int					parse_texture(t_map *map);
int					check_top_border(t_map map);
int					check_bottom_border(t_map map);
int					check_right_border(t_map map);
int					check_left_border(t_map map);
int					check_zero_surroundings(t_map map, int i, int j);
int					check_borders(t_map map);

// FREE

void				free_all(t_game *game);
void				free_text(t_map *map);
void				free_tab(char **tab);


#endif