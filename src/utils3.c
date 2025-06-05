/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:15:24 by maissat           #+#    #+#             */
/*   Updated: 2025/06/05 08:43:29 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_window_cross(t_game *game)
{
	free_all(game);
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

char	*ft_substr(char *str, int start, int end)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * (end - start + 1));
	if (!res)
		return (NULL);
	while (str[start] && start < end)
	{
		res[i] = str[start];
		i++;
		start++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i > 0)
	{
		if (s[i] == (char)c)
			return ((char *)(&s[i]));
		i--;
	}
	if (s[i] == (char)c)
		return ((char *)(&s[i]));
	return (0);
}
