/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissat <maissat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:42:09 by maissat           #+#    #+#             */
/*   Updated: 2025/04/25 19:09:57 by maissat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clear_image(t_game *game)
{
	ft_memset(game->data, 0, WIDTH * HEIGHT * (game->bbp / 8));
}

void	draw_square(int x, int y, int color, int size, t_game *game)
{
	int i; 
	
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
	//mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
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
				draw_square(j * 64, i * 64, color, 64, game);
			j++;
		}
		i++;
	}
	
}

int	touch(float ray_x, float ray_y, t_map map)
{
	int x;
	int y;
	
	x = ray_x / 64;
	y = ray_y / 64;
	 if (map.tab[y][x] == '1')
	 	return (1);
	return (0);
}

int	draw_loop(t_game *game)
{
	float ray_x;
	float ray_y;
	float cos_angle;
	float sin_angle;
	
	t_player *player;

	player = game->player;

	clear_image(game);
	move_player(player);
	draw_map(game);
	draw_square(player->x, player->y, 0x00FF00, 10, game);
	ray_x = player->x;
	ray_y = player->y;
	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);

	while (!touch(ray_x, ray_y, *(game->map)))
	{
		put_pixel(ray_x, ray_y, 0xFF0000, game);
		ray_x += cos_angle;
		ray_y += sin_angle;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	
	return (0);
}