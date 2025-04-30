/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:42:09 by maissat           #+#    #+#             */
/*   Updated: 2025/04/30 17:34:49 by root             ###   ########.fr       */
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
float	distance(float delta_x, float delta_y)
{
	return (sqrt(delta_x * delta_x + delta_y * delta_y));
}

float	fix_distance(float delta_x, float delta_y, t_game game)
{
	float angle = atan2(delta_y, delta_x) - game.player->angle;
	float fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}


void draw_column(t_player *player, t_game *game, float start_x, int i)
{
    float cos_angle = cos(start_x);
    float sin_angle = sin(start_x);
    float ray_x = player->x;
    float ray_y = player->y;

    while(!touch(ray_x, ray_y, *(game->map)))
    {
        //put_pixel(ray_x, ray_y, 0xFF0000, game);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
	float dist = fix_distance(ray_x -  player->x, ray_y - player->y, *game);
	float height = (64 / dist) * (WIDTH / 2 );
	int	start_y = (HEIGHT - height) / 2 ;
	int end = start_y + height;
	while (start_y < end)
	{
		put_pixel(i, start_y, 0x0db8e, game);
		start_y ++;
	}
}

int draw_loop(t_game *game)
{
    t_player *player = game->player;
    move_player(player);
    clear_image(game);
	//draw_square(player->x, player->y, 0x00FF00, 10, game);
	//draw_map(game);
    float fraction = PI / 3 / WIDTH;
    float start_x = player->angle - PI / 6;
    int i = 0;
    while(i < WIDTH)
    {
        draw_column(player, game, start_x, i);
        start_x += fraction;
        i++;
    }
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
    return 0;
}