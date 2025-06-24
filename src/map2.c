/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 01:55:31 by braugust          #+#    #+#             */
/*   Updated: 2025/06/25 01:57:32 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	process_map_line2(char *line, int *map_start, int *map_finish)
{
	int	i;

	i = 0;
	while (line && line[i] == ' ')
		i++;
	if (*map_finish)
	{
		if (!is_space_line(line))
			return (1);
	}
	if (!*map_start && line[i] == '1')
		*map_start = 1;
	if (*map_start && line[i] != '1')
		*map_finish = 1;
	return (0);
}

int	map_after_all(t_map map)
{
	int		fd;
	char	*line;
	int		map_finish;
	int		map_start;

	fd = open(map.name, O_RDONLY);
	if (fd == -1)
		return (1);
	map_finish = 0;
	map_start = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (process_map_line2(line, &map_start, &map_finish))
		{
			free(line);
			consume_remaining_file(fd);
			close(fd);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	validate_line_content(char *line)
{
	int	i;

	if (is_color_line(line) || is_texture_line(line))
		return (0);
	i = 0;
	while (line && line[i] == ' ')
		i++;
	if (line[i] != '1' && line[i] != '\n' && line[i] != '\0')
	{
		printf("Error\n Invalid line detected\n");
		return (1);
	}
	return (0);
}

int	check_invalid_lines(t_map map)
{
	int		fd;
	char	*line;

	fd = open(map.name, O_RDONLY);
	if (fd < 0)
		return (printf("Error\n Impossible to open %s\n", map.name), 1);
	line = get_next_line(fd);
	while (line)
	{
		if (validate_line_content(line))
		{
			free(line);
			consume_remaining_file(fd);
			close(fd);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}
