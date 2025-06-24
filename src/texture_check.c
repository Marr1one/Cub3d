/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:57:20 by root              #+#    #+#             */
/*   Updated: 2025/06/24 19:06:54 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	process_texture_lines(char **line, t_map *map, int fd)
{
	char	*trimmed;

	while (*line && is_texture_line(*line))
	{
		if (validate_texture_line_no_inner_spaces(*line))
		{
			printf("Error\nInvalid texture path: contains inner spaces => {%s}\n",
				*line);
			cleanup_remaining_lines(line, fd);
			exit(1);
		}
		trimmed = skip_spaces(*line);
		fill_texture(map, trimmed);
		free(trimmed);
		free(*line);
		*line = get_next_line(fd);
	}
}

void	fill_texture(t_map *map, char *trimmed)
{
	if (ft_strncmp(trimmed, "NO.", 3) == 0)
		map->no_texture = ft_strduptext(trimmed + 2);
	if (ft_strncmp(trimmed, "SO.", 3) == 0)
		map->so_texture = ft_strduptext(trimmed + 2);
	if (ft_strncmp(trimmed, "WE.", 3) == 0)
		map->we_texture = ft_strduptext(trimmed + 2);
	if (ft_strncmp(trimmed, "EA.", 3) == 0)
		map->ea_texture = ft_strduptext(trimmed + 2);
}

int	is_texture_line(char *line)
{
	int	i;

	i = 0;
	while (line && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (ft_strncmp(line + i, "NO", 2) == 0)
		return (1);
	else if (ft_strncmp(line + i, "SO", 2) == 0)
		return (1);
	else if (ft_strncmp(line + i, "EA", 2) == 0)
		return (1);
	else if (ft_strncmp(line + i, "WE", 2) == 0)
		return (1);
	return (0);
}

t_texture	*load_texture(void *mlx, char *path)
{
	t_texture	*tex;

	tex = malloc(sizeof(*tex));
	if (!tex)
		return (NULL);
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		free(tex);
		return (NULL);
	}
	tex->data = mlx_get_data_addr(tex->img, &tex->bpp, &tex->size_line,
			&tex->endian);
	return (tex);
}

void	init_textures(t_game *game, t_map *map)
{
	game->no = load_texture(game->mlx, map->no_texture);
	game->so = load_texture(game->mlx, map->so_texture);
	game->we = load_texture(game->mlx, map->we_texture);
	game->ea = load_texture(game->mlx, map->ea_texture);
	if (!game->no || !game->so || !game->we || !game->ea)
	{
		fprintf(stderr,
			"Error\nImpossible de charger une ou plusieurs textures\n");
		exit(1);
	}
}
