/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissat <maissat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 19:44:22 by root              #+#    #+#             */
/*   Updated: 2025/04/25 17:57:50 by maissat          ###   ########.fr       */
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
