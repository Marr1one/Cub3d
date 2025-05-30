/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 08:13:15 by braugust          #+#    #+#             */
/*   Updated: 2025/05/30 19:59:00 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fill_player_data(t_map *map, int i, int j)
{
	map->orientation = map->tab[i][j];
	map->player->x = j;
	map->player->y = i;
}

int	loop_check_chars(t_map *map, int i, int j, int *direction)
{
	if (*direction == 0 && (map->tab[i][j] == 'N' || map->tab[i][j] == 'S'))
	{
		fill_player_data(map, i, j);
		*direction = 1;
	}
	else if (*direction == 0 && (map->tab[i][j] == 'E'
		|| map->tab[i][j] == 'W'))
	{
		fill_player_data(map, i, j);
		*direction = 1;
	}
	else
	{
		if (*direction == 1 && is_direction(map->tab[i][j]))
			return (printf("Error\nMultiple player direction\n"), 1);
		return (printf("Error\nInvalid character in map\n"), 1);
	}
	return (0);
}

int	check_chars(t_map *map)
{
	int	i;
	int	j;
	int	direction;

	i = -1;
	direction = 0;
	while (map->tab[++i])
	{
		j = -1;
		while (map->tab[i][++j])
		{
			if (map->tab[i][j] != '1' && map->tab[i][j] != '0'
				&& map->tab[i][j] != ' ' && map->tab[i][j] != '\n')
			{
				if (loop_check_chars(map, i, j, &direction) == 1)
					return (1);
			}
		}
	}
	if (!direction)
		return (printf("Error\nNeed direction for the player\n"), 1);
	return (0);
}

int	valid_path(const char *path)
{
	int		fd;
	char	*ext;

	if (!path || !*path)
		return (printf("Error\n path empty !\n"), 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (printf("Erorr\n cannot open  %s !\n", path), 1);
	close(fd);
	ext = ft_strrchr(path, '.');
	if (!ext)
		return (printf("Error\n %s file has no extension\n", path), 1);
	if (ft_strcmp((char *)ext, ".xpm") != 0)
		return (printf("Error\n %s file must be .xpm\n", path), 1);
	return (0);
}

int	check_all_textures(const t_map *map)
{
	if (valid_path(map->no_texture))
		return (1);
	if (valid_path(map->so_texture))
		return (1);
	if (valid_path(map->we_texture))
		return (1);
	if (valid_path(map->ea_texture))
		return (1);
	return (0);
}
