/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:40:26 by braugust          #+#    #+#             */
/*   Updated: 2025/05/23 12:19:20 by braugust         ###   ########.fr       */
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

t_texture	*load_texture(void *mlx, char *path)
{
	t_texture	*tex;

	tex = malloc(sizeof(*tex));
	if (!tex)
		return (NULL);
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		free(tex);
		return (NULL);
	}
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line,
			&tex->endian);
	return (tex);
}

void	init_textures(t_game *game, t_map *map)
{
	game->no = load_texture(game->mlx, map->no_texture);
	game->so = load_texture(game->mlx, map->so_texture);
	game->we = load_texture(game->mlx, map->we_texture);
	game->ea = load_texture(game->mlx, map->ea_texture);
	if (!game->no || !game->so || !game->we || !game->ea)
	{
		fprintf(stderr,
			"Error\nImpossible de charger une ou plusieurs textures\n");
		exit(1);
	}
}
void	draw_column_textured(t_player *player, t_game *game, float ray_angle,
		int x)
{
	float			ray_dir_x;
	float			ray_dir_y;
	int				map_x;
	int				map_y;
	float			delta_dist_x;
	float			delta_dist_y;
	int				step_x;
	int				step_y;
	float			side_dist_x;
	float			side_dist_y;
	int				hit = 0, side;
	float			raw_dist;
	float			hit_x;
	float			hit_y;
	float			wall_x;
	float			perp_dist;
	t_texture		*tex;
	int				tex_x;
	int				line_height;
	int				start_y;
	int				end_y;
	int				y;
	int				d;
	int				tex_y;
	int				idx;
	unsigned char	b;
	unsigned char	g;
	unsigned char	r;
	int				color;

	ray_dir_x = cosf(ray_angle);
	ray_dir_y = sinf(ray_angle);
	map_x = (int)(player->x / 64);
	map_y = (int)(player->y / 64);
	delta_dist_x = (ray_dir_x != 0) ? fabsf(1.0f / ray_dir_x) : 1e30;
	delta_dist_y = (ray_dir_y != 0) ? fabsf(1.0f / ray_dir_y) : 1e30;
	step_x = (ray_dir_x < 0) ? -1 : 1;
	step_y = (ray_dir_y < 0) ? -1 : 1;
	side_dist_x = (ray_dir_x < 0) ? ((player->x - map_x * 64) / 64)
		* delta_dist_x : (((map_x + 1) * 64 - player->x) / 64) * delta_dist_x;
	side_dist_y = (ray_dir_y < 0) ? ((player->y - map_y * 64) / 64)
		* delta_dist_y : (((map_y + 1) * 64 - player->y) / 64) * delta_dist_y;
	hit = 0, side = 0;
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
		if (map_x < 0 || map_x >= game->map->width || map_y < 0
			|| map_y >= game->map->height)
			return ;
		if (game->map->tab[map_y][map_x] == '1')
			hit = 1;
	}
	raw_dist = (side == 0) ? (side_dist_x - delta_dist_x) * 64 : (side_dist_y
			- delta_dist_y) * 64;
	hit_x = player->x + raw_dist * ray_dir_x;
	hit_y = player->y + raw_dist * ray_dir_y;
	if (side == 0)
		wall_x = hit_y / 64.0f;
	else
		wall_x = hit_x / 64.0f;
	wall_x -= floorf(wall_x);
	if (wall_x < 0.0f)
		wall_x = 0.0f;
	perp_dist = raw_dist * cosf(ray_angle - player->angle);
	tex = NULL;
    if (side == 0)
    {
        if (step_x > 0)
            tex = game->we;
        else
            tex = game->ea;
    }
    else
    {
        if (step_y > 0)
            tex = game->so;
        else
            tex = game->no;
    }
	// Index horizontal dans la texture
	tex_x = (int)(wall_x * (float)tex->width);
	if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	// Couleurs plafond et sol
	int ceil_col = 0x87CEEB;  // bleu ciel
	int floor_col = 0x222222; // gris foncé
	line_height = (int)((64.0f / perp_dist) * (WIDTH / 2));
	start_y = (HEIGHT - line_height) / 2;
	end_y = start_y + line_height;
	if (start_y < 0)
		start_y = 0;
	if (end_y >= HEIGHT)
		end_y = HEIGHT - 1;
	// Plafond
	y = 0;
	while (y < start_y)
		put_pixel(x, y++, ceil_col, game);
	// Mur texturé
	y = start_y;
	while (y < end_y)
	{
		d = (y * 256) - (HEIGHT * 128) + (line_height * 128);
		tex_y = ((d * tex->height) / line_height) / 256;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		idx = tex_y * tex->size_line + tex_x * (tex->bpp / 8);
		if (idx < 0 || idx + 2 >= tex->size_line * tex->height)
		{
			y++;
			continue ;
		}
		b = tex->data[idx];
		g = tex->data[idx + 1];
		r = tex->data[idx + 2];
		color = (r << 16) | (g << 8) | b;
		put_pixel(x, y, color, game);
		y++;
	}
	// Sol
	y = end_y;
	while (y < HEIGHT)
		put_pixel(x, y++, floor_col, game);
}
