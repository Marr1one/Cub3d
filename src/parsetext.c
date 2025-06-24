/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsetext.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:40:34 by braugust          #+#    #+#             */
/*   Updated: 2025/06/24 19:23:30 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	validate_texture_line_no_inner_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strncmp(&line[i], "NO", 2) != 0 && ft_strncmp(&line[i], "SO", 2) != 0
		&& ft_strncmp(&line[i], "WE", 2) != 0 && ft_strncmp(&line[i], "EA",
			2) != 0)
		return (1);
	i += 2;
	while (line[i] == ' ')
		i++;
	while (line[i] && (line[i] != '\n' || line[i] != '\0'))
	{
		if (line[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	skip_empty_lines(char **line, int fd)
{
	if (*line && is_space_line(*line))
	{
		free(*line);
		*line = get_next_line(fd);
	}
}

int	check_end_of_parsing(char **line, int fd)
{
	if (*line && !is_color_line(*line) && !is_texture_line(*line)
		&& !is_space_line(*line))
	{
		cleanup_remaining_lines(line, fd);
		return (1);
	}
	return (0);
}

int	loop_parse_text(char *line, t_map *map, int fd)
{
	while (line)
	{
		if (line && is_color_line(line))
		{
			if (process_color_lines(&line, map, fd))
				return (1);
		}
		if (line && is_texture_line(line))
			process_texture_lines(&line, map, fd);
		if (line && is_space_line(line))
			skip_empty_lines(&line, fd);
		if (check_end_of_parsing(&line, fd))
			return (0);
	}
	return (0);
}

int	parse_texture(t_map *map)
{
	int		fd;
	char	*line;

	fd = open(map->name, O_RDONLY);
	line = get_next_line(fd);
	if (loop_parse_text(line, map, fd) != 0)
		return (1);
	close(fd);
	printf("no texture => {%s}\n", map->no_texture);
	printf("so texture => {%s}\n", map->so_texture);
	printf("we texture => {%s}\n", map->we_texture);
	printf("ea texture => {%s}\n", map->ea_texture);
	printf("ceiling color !------\n");
	show_int_tab(map->ceiling_color);
	printf("floor color !------\n");
	show_int_tab(map->floor_color);
	if (check_all_textures(map))
		return (1);
	return (0);
}
