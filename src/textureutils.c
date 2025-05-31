/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textureutils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:32:55 by braugust          #+#    #+#             */
/*   Updated: 2025/05/31 10:37:41 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	dda_while_loop(t_ray *ray, t_game *game)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_x >= game->map->width || ray->map_y < 0
			|| ray->map_y >= game->map->height)
			return (0);
		if (game->map->tab[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
	return (1);
}

float	get_wall_x(t_ray *ray, t_player *pl)
{
	float	hx;
	float	hy;
	float	wall_x;

	hx = pl->x + ray->raw_dist * ray->ray_dir_x;
	hy = pl->y + ray->raw_dist * ray->ray_dir_y;
	if (ray->side == 0)
		wall_x = hy / 64.0f;
	else
		wall_x = hx / 64.0f;
	wall_x -= floorf(wall_x);
	if (wall_x < 0.0f)
		wall_x = 0.0f;
	return (wall_x);
}

float	get_perp_dist(t_ray *ray, t_player *pl, float angle)
{
	return (ray->raw_dist * cosf(angle - pl->angle));
}

t_texture	*choose_tex(t_game *g, t_ray *r)
{
	if (r->side == 0)
	{
		if (r->step_x > 0)
			return (g->we);
		else
			return (g->ea);
	}
	else
	{
		if (r->step_y > 0)
			return (g->so);
		else
			return (g->no);
	}
}

int	get_tex_x(t_ray *r, t_texture *tex, float wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * (float)tex->width);
	if ((r->side == 0 && r->ray_dir_x > 0) || (r->side == 1
			&& r->ray_dir_y < 0))
		tex_x = tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}
