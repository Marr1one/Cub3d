/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:34:05 by root              #+#    #+#             */
/*   Updated: 2025/04/15 17:03:17 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_borders(t_map map)
{
	int	i;
	int	j;

	j = 0;
	while (map.tab[0][j] && map.tab[0][j] != '\n')
	{
		if (map.tab[0][j] != '1')
			return (printf("Top not closed\n"), 1);
		j++;
	}
	j = 0;
	while (map.tab[map.height - 1][j])
	{
		if (map.tab[map.height - 1][j] != '1')
			return (printf("Bottom not closed\n"), 1);
		j++;
	}
	i = 0;
	while (map.tab[i])
	{
		if (map.tab[i][0] != '1')
			return (printf("Left segment not closed\n"), 1);
		i++;
	}
	i = 0;
	while (map.tab[i])
	{
		j = 0;
		while (map.tab[i][j] != '\0' &&  map.tab[i][j] != '\n')
			j++;
		if (j > 2 && map.tab[i][j - 1] != '1')
			return (printf("Right segment not closed\n"), 1);
		i++;
	}
	return (0);
}

int	check_name(char *str)
{
	int i;

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
		return (printf("Name not valid!\n"), 1);
	map->name = map_name;
	map->height = get_height(map_name);
	if (map->height < 0)
		return (1);
	return (0);
}