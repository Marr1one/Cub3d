/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissat <maissat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:42:09 by maissat           #+#    #+#             */
/*   Updated: 2025/06/05 16:14:00 by maissat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clear_image(t_game *game)
{
	ft_memset(game->data, 0, WIDTH * HEIGHT * (game->bbp / 8));
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

void	draw_ceiling_and_floor(t_game *game)
{
	int	x;
	int	y;
	int	floor_color;
	int	ceiling_color;

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
				put_pixel(x, y, ceiling_color, game);
			else
				put_pixel(x, y, floor_color, game);
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
