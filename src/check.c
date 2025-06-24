/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:04:56 by maissat           #+#    #+#             */
/*   Updated: 2025/06/24 16:24:29 by braugust         ###   ########.fr       */
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

int	map_after_all(t_map map)
{
	int		fd;
	char	*line;
	int		map_finish;
	int		map_start;
	int		i;

	fd = open(map.name, O_RDONLY);
	map_finish = 0;
	map_start = 0;
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line && line[i] == ' ')
			i++;
		if (map_finish)
		{
			if (!is_space_line(line))
			{
				printf("ya des trucs apres map! a cette ligne ! => {%s}\n",
					line);
				free(line);
				close(fd);
				return (1);
			}
		}
		if (!map_start && line[i] == '1')
			map_start = 1;
		if (map_start && line[i] != '1')
			map_finish = 1;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	check_invalid_lines(t_map map)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(map.name, O_RDONLY);
	if (fd < 0)
		return (printf("Error\n Impossible to open %s\n", map.name), 1);
	line = get_next_line(fd);
	while (line)
	{
		if (!is_color_line(line) && !is_texture_line(line))
		{
			i = 0;
			while (line && line[i] == ' ')
				i++;
			if (line[i] != '1' && line[i] != '\n' && line[i] != '\0')
			{
				printf("Error\n Invalid line detected => {%s}\n", line);
				free(line);
				close(fd);
				return (1);
			}
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
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
		return (printf("truc apres la map a la fin !\n"), 1);
	if (count_color_line(*map) != 2)
		return (printf("pas assez ou trop de color_line\n"), 1);
	if (count_tex_line(*map) != 4)
		return (printf("pas assez ou trop de text_line\n"), 1);
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
