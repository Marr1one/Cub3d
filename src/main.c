/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:48:51 by root              #+#    #+#             */
/*   Updated: 2025/05/31 18:20:53 by root             ###   ########.fr       */
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

int	parse_texture(t_map *map)
{
	int		fd;
	char	*line;
	char	*trimmed;
	char	choice;

	fd = open(map->name, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		if (is_texture_line(line))
		{
			if (space_before(line))
				return (printf("Error\nSpace before texture\n"), 1);
			trimmed = skip_spaces(line);
			fill_texture(map, trimmed);
		}
		else if (is_color_line(line) != 0)
		{
			choice = is_color_line(line);
			if (space_before(line))
				return (printf("Error\nSpace before color\n"), 1);
			trimmed = skip_spaces(line);
			fill_color(map, trimmed, choice);
		}
		else
		{
			trimmed = skip_spaces(line);
			if (trimmed[0] && trimmed[0] == '1')
			{
				free(trimmed);
				break ;
			}
		}
		free(line);
		free(trimmed);
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
	//show_struct_map(map);
	game.map = &map;
	game.player = map.player;
	game.game_state = MENU_STATE;
	game.menu_selection = 0;
	init_game(&game, map);
	printf("ici tout va bien !\n");
	//mlx_hook(game.win, 2, 1L << 0, key_press, game.player);
	mlx_hook(game.win, 2, 1L << 0, global_key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, game.player);
	mlx_hook(game.win, 17, 0, close_window_cross, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
