/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissat <maissat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:15:24 by maissat           #+#    #+#             */
/*   Updated: 2025/05/22 17:48:52 by maissat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//void	init_player(t_player *player, char orientation, int map_x, int map_y)
//{
//	// Position du joueur (au centre de sa case)
//	player->x = map_x * TILE_SIZE + TILE_SIZE / 2;
//	player->y = map_y * TILE_SIZE + TILE_SIZE / 2;

//	// Orientation initiale en fonction de la lettre
//	if (orientation == 'N')
//		player->angle = M_PI_2;           // π/2 = vers le haut
//	else if (orientation == 'S')
//		player->angle = 3 * M_PI_2;       // 3π/2 = vers le bas
//	else if (orientation == 'E')
//		player->angle = 0;                // 0 = vers la droite
//	else if (orientation == 'W')
//		player->angle = M_PI;             // π = vers la gauche

//	// État des touches
//	player->key_up = 0;
//	player->key_down = 0;
//	player->key_left = 0;
//	player->key_right = 0;
//	player->left_rotate = 0;
//	player->right_rotate = 0;
//}
void	init_player(t_player *player, t_map map)
{
	player->x = map.player->x * 64 + 64 / 2;
	player->y = map.player->y * 64 + 64 / 2;
	if (map.orientation == 'N')
		player->angle = 3 * PI / 2;
	else if (map.orientation == 'S')
		player->angle = PI / 2;
	else if (map.orientation == 'E')
		player->angle = 0;
	else if (map.orientation == 'W')
		player->angle = PI;
	player->key_up = 0;
	player->key_down = 0;
	player->key_left = 0;
	player->key_right = 0;
	player->left_rotate = 0;
	player->right_rotate = 0;
}

void	init_game(t_game *game, t_map map)
{
	init_player(game->player, map);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bbp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	init_textures(game, &map);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
