/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:15:24 by maissat           #+#    #+#             */
/*   Updated: 2025/05/06 16:03:39 by root             ###   ########.fr       */
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

void	init_texture(t_game *game, t_map *map)
{
	game->no_text->img = mlx_xpm_file_to_image(game->mlx, map->no_texture, &game->no_text->width, &game->no_text->height);
	game->so_text->img = mlx_xpm_file_to_image(game->mlx, map->so_texture, &game->so_text->width, &game->so_text->height);
	game->ea_text->img = mlx_xpm_file_to_image(game->mlx, map->ea_texture, &game->ea_text->width, &game->ea_text->height);
	game->we_text->img = mlx_xpm_file_to_image(game->mlx, map->we_texture, &game->we_text->width, &game->we_text->height);
	//if (!game->no_text.img || !game->so_text.img || !game->ea_text.img || !game->we_text.img) {
    //    printf("Erreur : impossible de charger une texture\n");
    //    exit(1);
    //}
	game->no_text->data = mlx_get_data_addr(game->no_text->img, &game->no_text->bpp, &game->no_text->size_line, &game->no_text->endian);
	game->so_text->data = mlx_get_data_addr(game->so_text->img, &game->so_text->bpp, &game->so_text->size_line, &game->so_text->endian);
	game->ea_text->data = mlx_get_data_addr(game->ea_text->img, &game->ea_text->bpp, &game->ea_text->size_line, &game->ea_text->endian);
	game->we_text->data = mlx_get_data_addr(game->we_text->img, &game->we_text->bpp, &game->we_text->size_line, &game->we_text->endian);
}

void	init_game(t_game *game, t_map map)
{
	//game->no_text = malloc (sizeof(t_texture));
	//game->so_text = malloc (sizeof(t_texture));
	//game->we_text = malloc (sizeof(t_texture));
	//game->ea_text = malloc (sizeof(t_texture));
	//init_texture(game, &map);
	init_player(game->player, map);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bbp, &game->size_line, &game->endian);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}