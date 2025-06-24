/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:48:51 by root              #+#    #+#             */
/*   Updated: 2025/06/24 19:08:24 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	count_tex_line(t_map map)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(map.name, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (is_texture_line(line) != 0)
			count++;
		free(line);
		line = get_next_line(fd);
	}
	printf("count a la fin de tex_line ! count = {%d}\n", count);
	close(fd);
	return (count);
}

int	initialize_game(int argc, char **argv, t_game *game, t_map *map)
{
	ft_memset(game, 0, sizeof(t_game));
	ft_memset(map, 0, sizeof(t_map));
	map->player = malloc(sizeof(t_player));
	if (!map->player)
		return (printf("Memory allocation failed\n"), 1);
	if (argc != 2)
	{
		free(map->player);
		return (printf("Usage: ./cube3d map.cub\n"), 1);
	}
	if (check_map(argv[1], map) == 1)
	{
		free(map->player);
		free_tab(map->tab);
		free_text(map);
		return (1);
	}
	game->map = map;
	game->player = map->player;
	init_game(game, *map);
	return (0);
}

void	run_game_loop(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game->player);
	mlx_hook(game->win, 3, 1L << 1, key_release, game->player);
	mlx_hook(game->win, 17, 0, close_window_cross, game);
	mlx_loop_hook(game->mlx, draw_loop, game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_map	map;
	t_game	game;

	if (initialize_game(argc, argv, &game, &map) != 0)
		return (1);
	run_game_loop(&game);
	return (0);
}
