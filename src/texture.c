/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:40:26 by braugust          #+#    #+#             */
/*   Updated: 2025/05/16 02:40:24 by braugust         ###   ########.fr       */
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

t_texture *load_texture(void *mlx, char *path)
{
    t_texture *tex = malloc(sizeof(*tex));
    if (!tex)
        return NULL;
    tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
    if (!tex->img)
    {
        free(tex);
        return NULL;
    }
    tex->data = mlx_get_data_addr(tex->img,
                                  &tex->bpp,
                                  &tex->size_line,
                                  &tex->endian);
    return tex;
}

void init_textures(t_game *game, t_map *map)
{
    game->no = load_texture(game->mlx, map->no_texture);
    game->so = load_texture(game->mlx, map->so_texture);
    game->we = load_texture(game->mlx, map->we_texture);
    game->ea = load_texture(game->mlx, map->ea_texture);
    if (!game->no || !game->so || !game->we || !game->ea)
    {
        fprintf(stderr, "Error\nImpossible de charger une ou plusieurs textures\n");
        exit(1);
    }
}

void draw_column_textured(t_player *player, t_game *game,
                          float ray_angle, int x)
{
    // 1) DDA pour trouver hit, side, dist, step_x, step_y
    float ray_dir_x = cosf(ray_angle);
    float ray_dir_y = sinf(ray_angle);
    int map_x = (int)(player->x / 64);
    int map_y = (int)(player->y / 64);
    float delta_dist_x = fabsf(1.0f / ray_dir_x);
    float delta_dist_y = fabsf(1.0f / ray_dir_y);
    int step_x = (ray_dir_x < 0) ? -1 : 1;
    int step_y = (ray_dir_y < 0) ? -1 : 1;
    float side_dist_x = (ray_dir_x < 0)
        ? ((player->x - map_x*64) / 64) * delta_dist_x
        : (((map_x+1)*64 - player->x) / 64) * delta_dist_x;
    float side_dist_y = (ray_dir_y < 0)
        ? ((player->y - map_y*64) / 64) * delta_dist_y
        : (((map_y+1)*64 - player->y) / 64) * delta_dist_y;
    int hit = 0, side = 0;
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
    float perp_dist = (side == 0)
        ? (side_dist_x - delta_dist_x) * 64
        : (side_dist_y - delta_dist_y) * 64;
    perp_dist *= cosf(ray_angle - player->angle);

    // 2) Sélection de la bonne texture
    t_texture *tex;
    if (side == 0)
        tex = (step_x > 0 ? game->we : game->ea);
    else
        tex = (step_y > 0 ? game->so : game->no);

    // 3) Calcul de l’abscisse dans la texture
    float wall_x = (side == 0)
        ? (player->y + perp_dist*ray_dir_y) / 64.0f
        : (player->x + perp_dist*ray_dir_x) / 64.0f;
    wall_x -= floorf(wall_x);
    int tex_x = (int)(wall_x * tex->width);
    if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
        tex_x = tex->width - tex_x - 1;

    // 4) Projection et échantillonnage vertical
    int line_height = (int)((64.0f / perp_dist) * (WIDTH / 2));
    int start_y    = (HEIGHT - line_height) / 2;
    int end_y      = start_y + line_height;
    for (int y = start_y; y < end_y; y++)
    {
        int d = (y * 256) - (HEIGHT * 128) + (line_height * 128);
        int tex_y = ((d * tex->height) / line_height) / 256;
        int idx   = tex_y * tex->size_line + tex_x * (tex->bpp/8);
        unsigned char b = tex->data[idx];
        unsigned char g = tex->data[idx+1];
        unsigned char r = tex->data[idx+2];
        int color = (r << 16) | (g << 8) | b;
        put_pixel(x, y, color, game);
    }
}
