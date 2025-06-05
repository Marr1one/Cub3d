/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissat <maissat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:48:51 by braugust          #+#    #+#             */
/*   Updated: 2025/06/05 17:29:23 by maissat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_walkable(t_map *map, float x, float y)
{
	int	map_x;
	int	map_y;

	map_x = (int)(x / 64);
	map_y = (int)(y / 64);
	if (map_y < 0 || map_y >= map->height)
		return (0);
	if (map_x < 0 || map_x >= map->width)
		return (0);
	if (map->tab[map_y][map_x] == '1')
		return (0);
	return (1);
}

int	can_move(t_map *map, float x, float y)
{
	if (!is_walkable(map, x + PLAYER_RADIUS, y + PLAYER_RADIUS))
		return (0);
	if (!is_walkable(map, x + PLAYER_RADIUS, y - PLAYER_RADIUS))
		return (0);
	if (!is_walkable(map, x - PLAYER_RADIUS, y + PLAYER_RADIUS))
		return (0);
	if (!is_walkable(map, x - PLAYER_RADIUS, y - PLAYER_RADIUS))
		return (0);
	return (1);
}
