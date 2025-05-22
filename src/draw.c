/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissat <maissat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:42:09 by maissat           #+#    #+#             */
/*   Updated: 2025/05/22 17:47:13 by maissat          ###   ########.fr       */
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
	// mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
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

// void draw_column(t_player *player, t_game *game, float start_x, int i)
//{
//	(void)i;
//    float cos_angle = cos(start_x);
//    float sin_angle = sin(start_x);
//    float ray_x = player->x;
//    float ray_y = player->y;
// void draw_column(t_player *player, t_game *game, float start_x, int i)
//{
//	(void)i;
//    float cos_angle = cos(start_x);
//    float sin_angle = sin(start_x);
//    float ray_x = player->x;
//    float ray_y = player->y;

//    while(!touch(ray_x, ray_y, *(game->map)))
//    {
//        //put_pixel(ray_x, ray_y, 0xFF0000, game);
//        ray_x += cos_angle;
//        ray_y += sin_angle;
//    }

//	float dist = fix_distance(ray_x -  player->x, ray_y - player->y, *game);
//	float height = (64 / dist) * (WIDTH / 2 );
//	int	start_y = (HEIGHT - height) / 2 ;
//	int end = start_y + height;
//	while (start_y < end)
//	{
//		put_pixel(i, start_y, 0x00FF00, game);
//		start_y ++;
//	}
//}

void	draw_column(t_player *player, t_game *game, float ray_angle, int i)
{
	float	ray_dir_x;
	float	ray_dir_y;
	int		map_x;
	int		map_y;
	float	delta_dist_x;
	float	delta_dist_y;
	int		step_x;
	int		step_y;
	float	side_dist_x;
	float	side_dist_y;
	int		hit;
	int		side;
	float	dist;
	float	height;
	int		start_y;
	int		end_y;
	int		color;

	ray_dir_x = cos(ray_angle);
	ray_dir_y = sin(ray_angle);
	// Position du joueur en cases
	map_x = (int)(player->x / 64);
	map_y = (int)(player->y / 64);
	// Distance que le rayon doit parcourir pour atteindre le prochain carré en X ou Y
	delta_dist_x = fabs(1.0f / ray_dir_x);
	delta_dist_y = fabs(1.0f / ray_dir_y);
	if (ray_dir_x < 0)
		step_x = -1;
	else
		step_x = 1;
	if (ray_dir_y < 0)
		step_y = -1;
	else
		step_y = 1;
	if (ray_dir_x < 0)
		side_dist_x = ((player->x - map_x * 64) / 64) * delta_dist_x;
	else
		side_dist_x = (((map_x + 1) * 64 - player->x) / 64) * delta_dist_x;
	if (ray_dir_y < 0)
		side_dist_y = (player->y - map_y * 64) / 64 * delta_dist_y;
	else
		side_dist_y = ((map_y + 1) * 64 - player->y) / 64 * delta_dist_y;
	hit = 0;
	side = 0;
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (game->map->tab[map_y][map_x] == '1')
			hit = 1;
	}
	if (side == 0)
		dist = (side_dist_x - delta_dist_x) * 64;
	else
		dist = (side_dist_y - delta_dist_y) * 64;
	dist *= cos(ray_angle - player->angle);
	// Hauteur de la colonne
	height = (64 / dist) * (WIDTH / 2);
	start_y = (HEIGHT - height) / 2;
	end_y = start_y + height;
	// Couleur selon la direction
	if (side == 0)
	{
		if (step_x > 0)
			color = 0x00FF00; // Est → vert
		else
			color = 0x0000FF; // Ouest → bleu
	}
	else
	{
		if (step_y > 0)
			color = 0xFFFFFF; // Sud → blanc
		else
			color = 0xFF0000; // Nord → rouge
	}
	// Dessin de la colonne verticale
	while (start_y < end_y)
	{
		put_pixel(i, y, color, game);
		y++;
	}
}
//    while(!touch(ray_x, ray_y, *(game->map)))
//    {
//        //put_pixel(ray_x, ray_y, 0xFF0000, game);
//        ray_x += cos_angle;
//        ray_y += sin_angle;
//    }

//	float dist = fix_distance(ray_x -  player->x, ray_y - player->y, *game);
//	float height = (64 / dist) * (WIDTH / 2 );
//	int	start_y = (HEIGHT - height) / 2 ;
//	int end = start_y + height;
//	while (start_y < end)
//	{
//		put_pixel(i, start_y, 0x00FF00, game);
//		start_y ++;
//	}
//}

// void draw_column(t_player *player, t_game *game, float ray_angle, int i)
//{
//	float ray_dir_x = cos(ray_angle);
//	float ray_dir_y = sin(ray_angle);

//	// Position du joueur en cases
//	int map_x = (int)(player->x / 64);
//	int map_y = (int)(player->y / 64);

//	// Distance que le rayon doit parcourir pour atteindre le prochain carré en X ou Y
//	float delta_dist_x = fabs(1.0f / ray_dir_x);
//	float delta_dist_y = fabs(1.0f / ray_dir_y);

//	int step_x;
//	if (ray_dir_x < 0)
//		step_x = -1;
//	else
//		step_x =  1;
//	int step_y;
//	if (ray_dir_y < 0)
//		step_y = -1;
//	else
//		step_y =  1;

//	float side_dist_x;
//	if (ray_dir_x < 0)
//		side_dist_x = ((player->x - map_x * 64) / 64) * delta_dist_x;
//	else
//		side_dist_x = (((map_x + 1) * 64 - player->x) / 64) * delta_dist_x;
//	float side_dist_y;
//	if (ray_dir_y < 0)
//		side_dist_y = (player->y - map_y * 64) / 64 * delta_dist_y;
//	else
//		side_dist_y = ((map_y + 1) * 64 - player->y) / 64 * delta_dist_y;

//	int hit = 0;
//	int side = 0;

//	while (!hit)
//	{
//		if (side_dist_x < side_dist_y)
//		{
//			side_dist_x += delta_dist_x;
//			map_x += step_x;
//			side = 0;
//		}
//		else
//		{
//			side_dist_y += delta_dist_y;
//			map_y += step_y;
//			side = 1;
//		}
//		if (game->map->tab[map_y][map_x] == '1')
//			hit = 1;
//	}

//	float dist;
//	if (side == 0)
//		dist = (side_dist_x - delta_dist_x) * 64;
//	else
//		dist = (side_dist_y - delta_dist_y) * 64;
//	dist *= cos(ray_angle - player->angle);
//	// Hauteur de la colonne
//	float height = (64 / dist) * (WIDTH / 2);
//	int start_y = (HEIGHT - height) / 2;
//	int end_y = start_y + height;

//	// Couleur selon la direction
//	int color;
//	if (side == 0)
//	{
//		if (step_x > 0)
//			color = 0x00FF00; // Est → vert
//		else
//			color = 0x0000FF; // Ouest → bleu
//	}
//	else
//	{
//		if (step_y > 0)
//			color = 0xFFFFFF; // Sud → blanc
//		else
//			color = 0xFF0000; // Nord → rouge
//	}

//	// Dessin de la colonne verticale
//	for (int y = start_y; y < end_y; y++)
//		put_pixel(i, y, color, game);
//}

void	draw_ceiling_and_floor(t_game *game)
{
	int	mid;
	int	x;
	int	y;

	mid = HEIGHT / 2;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < mid)
				put_pixel(x, y, 0x87CEEB, game); // ciel bleu clair
			else
				put_pixel(x, y, 0x2E2B2B, game); // sol gris sombre
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
