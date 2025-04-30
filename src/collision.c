/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:48:51 by braugust          #+#    #+#             */
/*   Updated: 2025/04/30 18:49:21 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_walkable(t_map *map, float x, float y)
{
	int	cell_x;
	int	cell_y;

	cell_x = (int)(x / 64);
	cell_y = (int)(y / 64);
	if (cell_y < 0 || cell_y >= map->height)
		return (0);
	if (cell_x < 0 || cell_x >= map->width)
		return (0);
	return (map->tab[cell_y][cell_x] != '1');
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
