/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:44:22 by root              #+#    #+#             */
/*   Updated: 2025/05/27 12:29:07 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	init_ray_dir(t_player *player, float ray_angle, t_ray *ray)
{
	ray->ray_dir_x = cosf(ray_angle);
	ray->ray_dir_y = sinf(ray_angle);
	ray->map_x = (int)(player->x / 64);
	ray->map_y = (int)(player->y / 64);
	if (ray->ray_dir_x != 0)
		ray->delta_dist_x = fabsf(1.0f / ray->ray_dir_x);
	else
		ray->delta_dist_x = 1e30;
	if (ray->ray_dir_y != 0)
		ray->delta_dist_y = fabsf(1.0f / ray->ray_dir_y);
	else
		ray->delta_dist_y = 1e30;
	if (ray->ray_dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->ray_dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;
}

void	init_ray_side_dist(t_player *player, t_ray *ray)
{
	if (ray->ray_dir_x < 0)
		ray->side_dist_x = ((player->x - ray->map_x * 64) / 64)
			* ray->delta_dist_x;
	else
		ray->side_dist_x = (((ray->map_x + 1) * 64 - player->x) / 64)
			* ray->delta_dist_x;
	if (ray->ray_dir_y < 0)
		ray->side_dist_y = ((player->y - ray->map_y * 64) / 64)
			* ray->delta_dist_y;
	else
		ray->side_dist_y = (((ray->map_y + 1) * 64 - player->y) / 64)
			* ray->delta_dist_y;
}

void	init_ray(t_player *player, float ray_angle, t_ray *ray)
{
	init_ray_dir(player, ray_angle, ray);
	init_ray_side_dist(player, ray);
}

int	raycast_wall(t_player *player, t_game *game, float ray_angle, t_ray *ray)
{
	init_ray(player, ray_angle, ray);
	if (!dda_while_loop(ray, game))
		return (0);
	if (ray->side == 0)
		ray->raw_dist = (ray->side_dist_x - ray->delta_dist_x) * 64;
	else
		ray->raw_dist = (ray->side_dist_y - ray->delta_dist_y) * 64;
	return (1);
}
