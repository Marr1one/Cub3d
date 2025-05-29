/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:57:20 by root              #+#    #+#             */
/*   Updated: 2025/05/29 11:41:31 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	if (str_in_str(line, "NO"))
		return (1);
	else if (str_in_str(line, "SO"))
		return (1);
	else if (str_in_str(line, "WE"))
		return (1);
	else if (str_in_str(line, "EA"))
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
