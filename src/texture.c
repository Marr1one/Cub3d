/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissat <maissat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:40:26 by braugust          #+#    #+#             */
/*   Updated: 2025/05/22 17:49:05 by maissat          ###   ########.fr       */
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
	int				hit;
	float			perp_dist;
	t_texture		*tex;
	float			wall_x;
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
	int				side;
	int				ceil_col;
	int				floor_col;
	int				step_x;
	int				step_y;
	float			side_dist_x;
	float			side_dist_y;
	float			delta_dist_x;
	float			delta_dist_y;

	hit = 0;
	ray_dir_x = cosf(ray_angle);
	ray_dir_y = sinf(ray_angle);
	map_x = (int)(player->x / 64);
	map_y = (int)(player->y / 64);
	hit = 0;
	side = 0;
	if (ray_dir_x != 0)
		delta_dist_x = fabsf(1.0f / ray_dir_x);
	else
		delta_dist_x = 1e30;
	if (ray_dir_y != 0)
		delta_dist_y = fabsf(1.0f / ray_dir_y);
	else
		delta_dist_y = 1e30;
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = ((player->x - map_x * 64) / 64) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (((map_x + 1) * 64 - player->x) / 64) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = ((player->y - map_y * 64) / 64) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (((map_y + 1) * 64 - player->y) / 64) * delta_dist_y;
	}
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
		perp_dist = (side_dist_x - delta_dist_x) * 64;
	else
		perp_dist = (side_dist_y - delta_dist_y) * 64;
	perp_dist *= cosf(ray_angle - player->angle);
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
	if (side == 0)
		wall_x = (player->y + perp_dist * ray_dir_y) / 64.0f;
	else
		wall_x = (player->x + perp_dist * ray_dir_x) / 64.0f;
	wall_x -= floorf(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	ceil_col = 0x87CEEB;// bleu ciel
	floor_col = 0x222222;// gris
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
	{
		put_pixel(x, y, ceil_col, game);
		y++;
	}
	// Mur texturé
	y = start_y;
	while (y < end_y)
	{
		d = (y * 256) - (HEIGHT * 128) + (line_height * 128);
		tex_y = ((d * tex->height) / line_height) / 256;
		idx = tex_y * tex->size_line + tex_x * (tex->bpp / 8);
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
	{
		put_pixel(x, y, floor_col, game);
		y++;
	}
}
