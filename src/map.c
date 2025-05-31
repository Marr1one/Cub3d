/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 11:02:03 by braugust          #+#    #+#             */
/*   Updated: 2025/05/31 12:58:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	show_struct_map(t_map map)
{
	printf("map height => %d\n", map.height);
	printf("map width => %d\n", map.width);
	printf("map name => %s\n", map.name);
	printf("map orientation => {%c}\n", map.orientation);
	printf("la map ! -----------------\n");
	show_tab(map.tab);
	printf("---------\n");
	printf("no texture => {%s}\n", map.no_texture);
	printf("so texture => {%s}\n", map.so_texture);
	printf("we texture => {%s}\n", map.we_texture);
	printf("ea texture => {%s}\n", map.ea_texture);
	printf("ceiling color !------\n");
	show_int_tab(map.ceiling_color);
	printf("floor color !------\n");
	show_int_tab(map.floor_color);
}

int	process_map_line(char *line, int *map_started, t_map *map)
{
	int	i;

	i = 0;
	if (*map_started == 0)
	{
		while (line[i] == ' ')
			i++;
		if (line[i] == '1')
			*map_started = 1;
	}
	if (*map_started)
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] != '1')
		{
			if (line[i] == '\n' || line[i] == '\0')
				return (1);
			return (printf("Error\nLeft segment open\n"), -1);
		}
		map->width = ft_max(map->width, ft_strlen(line));
		return (2);
	}
	return (0);
}

int	parse_map_lines(int fd, t_map *map)
{
	char	*line;
	int		count;
	int		map_started;
	int		res;

	count = 0;
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		res = process_map_line(line, &map_started, map);
		if (res == 1)
		{
			free(line);
			break ;
		}
		if (res == -1)
			return (free(line), -1);
		if (res == 2)
			count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

int	get_height(char *map_name, t_map *map)
{
	int	fd;
	int	count;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nImpossible to open the map!\n"), -1);
	count = parse_map_lines(fd, map);
	close(fd);
	return (count);
}
