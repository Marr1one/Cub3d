/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:34:05 by root              #+#    #+#             */
/*   Updated: 2025/04/23 00:45:45 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//int	check_borders(t_map map)
//{
//	int	i;
//	int	j;

//	j = 0;
//	while (map.tab[0][j] && map.tab[0][j] != '\n')
//	{
//		if (map.tab[0][j] != '1')
//			return (printf("Top not closed\n"), 1);
//		j++;
//	}
//	j = 0;
//	while (map.tab[map.height - 1][j])
//	{
//		if (map.tab[map.height - 1][j] != '1')
//			return (printf("Bottom not closed\n"), 1);
//		j++;
//	}
//	i = 0;
//	while (map.tab[i])
//	{
//		j = 0;int	check_borders(t_map map)
//{
//	int	i;
//	int	j;

//	j = 0;
//	while (map.tab[0][j] && map.tab[0][j] != '\n')
//	{
//		if (map.tab[0][j] != '1')
//			return (printf("Top not closed\n"), 1);
//		j++;
//	}
//	j = 0;
//	while (map.tab[map.height - 1][j])
//	{
//		if (map.tab[map.height - 1][j] != '1')
//			return (printf("Bottom not closed\n"), 1);
//		j++;
//	}
//	i = 0;
//	while (map.tab[i])
//	{
//		j = 0;
//		while (map.tab[i][j] == ' ')
//			j++;
//		if (map.tab[i][j] != '1')
//			return (printf("Left segment not closed\n"), 1);
//		i++;
//	}
//	i = 0;
//	while (map.tab[i])
//	{
//		j = 0;
//		while (map.tab[i][j] != '\0' &&  map.tab[i][j] != '\n')
//			j++;
//		if (j > 2 && map.tab[i][j - 1] != '1')
//			return (printf("Right segment not closed\n"), 1);
//		i++;
//	}
//	return (0);
//}
//		while (map.tab[i][j] == ' ')
//			j++;
//		if (map.tab[i][j] != '1')
//			return (printf("Left segment not closed\n"), 1);
//		i++;
//	}
//	i = 0;
//	while (map.tab[i])
//	{
//		j = 0;
//		while (map.tab[i][j] != '\0' &&  map.tab[i][j] != '\n')
//			j++;
//		if (j > 2 && map.tab[i][j - 1] != '1')
//			return (printf("Right segment not closed\n"), 1);
//		i++;
//	}
//	return (0);
//}

int	is_direction(char c)
{
	if (c == 'N' || c == 'S')
		return (1);
	if (c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	check_borders(t_map map)
{
	int	i;
	int	j;

	j = 0;
	while (map.tab[0][j] && map.tab[0][j] != '\n')
	{
		while (map.tab[0][j] == ' ')
			j++;
		if (map.tab[0][j] != '1')
			return (printf("Error\nTop not closed\n"), 1);
		j++;
	}
	j = 0;
	while (map.tab[map.height - 1][j])
	{
		while (map.tab[map.height - 1][j] == ' ')
			j++;
		if (map.tab[map.height - 1][j] != '1')
		{
			if (map.tab[map.height - 1][j] == '\n' || map.tab[map.height - 1][j] == '\0')
				break;
			return (printf("Error\nBottom not closed\n"), 1);
		}
		j++;
	}
	i = 0;
	while (map.tab[i])
	{
		j = 0;
		while (map.tab[i][j] != '\0' &&  map.tab[i][j] != '\n')
			j++;
		if (j > 2 && map.tab[i][j - 1] != '1')
		{
			return (printf("Error\nRight segment not closed on line %d\n", i), 1);
		}
		i++;
	}
	i = 0;
	while (map.tab[i])
	{
		j = 0;
		while (map.tab[i][j] == ' ')
			j++;
		if (map.tab[i][j] != '1')
		{
			return (printf("Error\nLeft border not closed\n"), 1);
		}
		i++;
	}
	i = 0;
	while (map.tab[i])
	{
		j = 0;
		while (map.tab[i][j])
		{
			if (map.tab[i][j] == '0')
			{
				if (map.tab[i - 1] && (ft_strlen(map.tab[i - 1]) < j))
					return (printf("Error\nmap no closed on line %d\n", i), 1);
				if (map.tab[i + 1] && (ft_strlen(map.tab[i + 1]) < j))
					return (printf("Error\nmap no closed on line %d\n", i), 1);
				if (map.tab[i + 1] && (map.tab[i + 1][j] != '1' && map.tab[i + 1][j] != '0' && is_direction(map.tab[i + 1][j]) == 0))
					return (printf("Error\nmap no closed on line %d\n", i), 1);
				if (map.tab[i - 1] && (map.tab[i - 1][j] != '1' && map.tab[i - 1][j] != '0' && is_direction(map.tab[i - 1][j]) == 0))
					return (printf("Error\nmap no closed on line %d\n", i), 1);
			}
			j++;
		}
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
		return (printf("Error\nName not valid!\n"), 1);
	map->name = map_name;
	map->height = get_height(map_name, map);
	if (map->height < 0)
		return (1);
	create_tab(map);
	if (parse_texture(map) != 0)
		return (1);
	if (check_chars(*map) != 0)
		return (1);
	if (check_borders(*map) != 0)
		return (1);
	return (0);
}

int	check_chars(t_map map)
{
	int	i;
	int	j;
	int	direction;

	i = 0;
	direction = 0;
	while (map.tab[i])
	{
		j = 0;
		while (map.tab[i][j])
		{
			if (map.tab[i][j] != '1' && map.tab[i][j] != '0'  && map.tab[i][j] != ' ' && map.tab[i][j] != '\n')
			{
				if (direction == 0 && (map.tab[i][j] == 'N' || map.tab[i][j] == 'S'))
					direction = 1;
				else if (direction == 0 && (map.tab[i][j] == 'E' || map.tab[i][j] == 'W'))
					direction = 1;
				else
				{
					if (direction == 1 && is_direction(map.tab[i][j]))
						return (printf("Error\nMultiple player direction\n"), 1);
					return (printf("Error\nInvalid character in map\n"), 1);
				}
			}
			j++;
		}
		i++;
	}
	if (!direction)
		return (printf("Error\nNeed direction for the player\n"), 1);
	return (0);
}