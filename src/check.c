/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:04:56 by maissat           #+#    #+#             */
/*   Updated: 2025/06/25 01:56:32 by braugust         ###   ########.fr       */
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
		return (printf("Error\nName not valid!\n"), 1);
	map->name = map_name;
	map->height = get_height(map_name, map);
	if (map->height <= 0)
		return (1);
	if (map_after_all(*map) != 0)
		return (printf("Error\n map not at the end of .cub !\n"), 1);
	if (count_color_line(*map) != 2)
		return (printf("Error\n Not the right number of color lines!\n"), 1);
	if (count_tex_line(*map) != 4)
		return (printf("Error\n Not the right number of texture lines\n"), 1);
	if (check_invalid_lines(*map) != 0)
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
