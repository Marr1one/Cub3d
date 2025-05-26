/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:42:09 by maissat           #+#    #+#             */
/*   Updated: 2025/05/26 13:16:16 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clear_image(t_game *game)
{
	ft_memset(game->data, 0, WIDTH * HEIGHT * (game->bbp / 8));
}

void	draw_square(int x, int y, int color, int size, t_game *game)
{
	int	i;

	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + size, y + i, color, game);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y + size, color, game);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	draw_map(t_game *game)
{
	char	**tab;
	int		color;
	int		i;
	int		j;

	tab = game->map->tab;
	color = 0x0000ff;
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '1')
				draw_square(j * 32, i * 32, color, 64, game);
			j++;
		}
		i++;
	}
}

int	touch(float ray_x, float ray_y, t_map map)
{
	int	x;
	int	y;

	x = ray_x / 64;
	y = ray_y / 64;
	if (map.tab[y][x] == '1')
		return (1);
	return (0);
}

float	distance(float delta_x, float delta_y)
{
	return (sqrt(delta_x * delta_x + delta_y * delta_y));
}

float	fix_distance(float delta_x, float delta_y, t_game game)
{
	float	angle;
	float	fix_dist;

	angle = atan2(delta_y, delta_x) - game.player->angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

unsigned	int rgb_to_hex_int(int r, int g, int b)
{
	unsigned int	hex;

	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	hex = (r << 16) | (g << 8) | b;
	return (hex);
}

void	draw_ceiling_and_floor(t_game *game)
{
	int				x;
	int				y;
	unsigned int	floor_color;
	unsigned int	ceiling_color;

	floor_color = rgb_to_hex_int(game->map->floor_color[0],
			game->map->floor_color[1], game->map->floor_color[2]);
	ceiling_color = rgb_to_hex_int(game->map->ceiling_color[0],
			game->map->ceiling_color[1], game->map->ceiling_color[2]);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(x, y, floor_color, game);
			else
				put_pixel(x, y, ceiling_color, game);
			x++;
		}
		y++;
	}
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	player = game->player;
	move_player(player, game->map);
	clear_image(game);
	// draw_square(player->x, player->y, 0x00FF00, 10, game);
	// draw_map(game);
	draw_ceiling_and_floor(game);
	fraction = PI / 3 / WIDTH;
	start_x = player->angle - PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_column_textured(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
