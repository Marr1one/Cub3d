/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:40:26 by braugust          #+#    #+#             */
/*   Updated: 2025/05/06 18:15:43 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// // Charge un fichier XPM et remplit la structure texture
// int	load_one_texture(void *mlx, t_texture *tex, const char *path)
// {
// 	// 1) Charge l’image
// 	tex->img_ptr = mlx_xpm_file_to_image(mlx, (char *)path, &tex->width,
// 			&tex->height);
// 	if (!tex->img_ptr)
// 		return (printf("Error\nCannot load texture %s\n", path), 1);
// 	// 2) Récupère le buffer de pixels
// 	tex->data = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_size,
// 			&tex->bpp /* endian non utilisé ici */);
// 	// Note : MLX rend parfois bpp et endian ; on stocke juste bpp et line_size
// 	return (0);
// }

// // Charge toutes les textures du jeu
// int	load_textures(t_game *game, t_map *map)
// {
// 	if (load_one_texture(game->mlx, &game->north, map->no_texture))
// 		return (1);
// 	if (load_one_texture(game->mlx, &game->south, map->so_texture))
// 		return (1);
// 	if (load_one_texture(game->mlx, &game->west, map->we_texture))
// 		return (1);
// 	if (load_one_texture(game->mlx, &game->east, map->ea_texture))
// 		return (1);
// 	return (0);
// }
