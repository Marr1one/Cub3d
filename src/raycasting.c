/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:44:22 by root              #+#    #+#             */
/*   Updated: 2025/04/24 22:05:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;
	
	if (x > WIDTH || y > HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * (game->bbp / 8);
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bbp, &game->size_line, &game->endian);
	
}