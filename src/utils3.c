/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:51:29 by root              #+#    #+#             */
/*   Updated: 2025/05/27 12:01:50 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_window_cross(void)
{
	exit(0);
}

int	touch(float ray_x, float ray_y, t_map map)
{
	int	x;
	int	y;

	x = ray_x / 64;
	y = ray_y / 64;
	if (map.tab[y][x] == '1')
		return (1);
	return (0);
}


int	rgb_to_hex_int(int r, int g, int b)
{
	unsigned int	hex;

	if (r < 0)
		r = 0;
	if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	if (b > 255)
		b = 255;
	hex = (r << 16) | (g << 8) | b;
	return (hex);
}
