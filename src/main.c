/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:48:51 by root              #+#    #+#             */
/*   Updated: 2025/06/05 08:42:12 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	show_int_tab(int *tab)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		printf("%d\n", tab[i]);
		i++;
	}
}

int	loop_parse_text(char *line, t_map *map)
{
	char	choice;
	char	*trimmed;

	if (is_texture_line(line))
	{
		if (space_before(line))
			return (printf("Error\nSpace before texture\n"), 1);
		trimmed = skip_spaces(line);
		fill_texture(map, trimmed);
		return (free(trimmed), 0);
	}
	else if (is_color_line(line) != 0)
	{
		choice = is_color_line(line);
		if (space_before(line))
			return (printf("Error\nSpace before color\n"), 1);
		trimmed = skip_spaces(line);
		fill_color(map, trimmed, choice);
		return (free(trimmed), 0);
	}
	return (0);
}

int	parse_texture(t_map *map)
{
	int		fd;
	char	*line;

	fd = open(map->name, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		loop_parse_text(line, map);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	if (check_all_textures(map))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	ft_memset(&map, 0, sizeof(t_map));
	map.player = malloc(sizeof(t_player));
	if (argc != 2)
		return (printf("Usage: ./cube3d map.cub\n"), 1);
	if (check_map(argv[1], &map) == 1)
		return (1);
	show_struct_map(map);
	game.map = &map;
	game.player = map.player;
	init_game(&game, map);
	mlx_hook(game.win, 2, 1L << 0, key_press, game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, game.player);
	mlx_hook(game.win, 17, 0, close_window_cross, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	free_all(&game);
	return (0);
}
