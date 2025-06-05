/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissat <maissat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:04:56 by maissat           #+#    #+#             */
/*   Updated: 2025/06/05 15:49:32 by maissat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_direction(char c)
{
	if (c == 'N' || c == 'S')
		return (1);
	if (c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	check_inner_map(t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (map.tab[i])
	{
		j = 0;
		while (map.tab[i][j])
		{
			if (map.tab[i][j] == '0')
				if (check_zero_surroundings(map, i, j))
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_borders(t_map map)
{
	if (check_top_border(map))
		return (1);
	if (check_bottom_border(map))
		return (1);
	if (check_right_border(map))
		return (1);
	if (check_left_border(map))
		return (1);
	if (check_inner_map(map))
		return (1);
	return (0);
}

int	check_name(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '.')
		return (1);
	while (str[i] && str[i] != '.')
		i++;
	if (str[i] != '.')
		return (1);
	if (ft_strcmp(str + i, ".cub") != 0)
		return (1);
	return (0);
}

int	check_map(char *map_name, t_map *map)
{
	if (check_name(map_name) == 1)
	{
		free(map->player);
		return (printf("Error\nName not valid!\n"), 1);
	}
	map->name = map_name;
	map->height = get_height(map_name, map);
	if (map->height <= 0)
		return (1);
	create_tab(map);
	if (parse_texture(map) != 0)
		return (1);
	if (check_chars(map) != 0)
		return (1);
	if (check_borders(*map) != 0)
		return (1);
	return (0);
}
