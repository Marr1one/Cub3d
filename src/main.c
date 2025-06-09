/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:48:51 by root              #+#    #+#             */
/*   Updated: 2025/06/09 18:25:26 by braugust         ###   ########.fr       */
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

int	is_space_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			if (line[i] == '\n')
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_start_map(char *line)
{
	int	i;
	
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			if (line[i] != '1')
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

int	loop_parse_text(char *line, t_map *map, int fd)
{
	char	choice;
	char	*trimmed;
	int		count1;
	int		count2;

	count1 = 0;
	count2 = 0;

	if (is_color_line(line) || is_texture_line(line))
	{
		while (is_color_line(line)|| is_space_line(line))
		{
			choice = is_color_line(line);
			if (space_before(line))
				return (printf("Error\nSpace before color\n"), 1);
			trimmed = skip_spaces(line);
			if (!is_space_line(line))
			{
				if (fill_color(map, trimmed, choice, &count1))
					return (1);
				
			}
			free(trimmed);
			line = get_next_line(fd);
		}
		while (is_texture_line(line) || is_space_line(line))
		{
			if (space_before(line))
				return (printf("Error\nSpace before texture \n"), 1);
			trimmed = skip_spaces(line);
			fill_texture(map, trimmed, &count2);
			free(trimmed);
			line = get_next_line(fd);
		}
		printf("%d\n", count1);
		printf("%d\n", count2);
		if (count2 != 4)
			return (printf("Parsing problem in text! \na cette ligne =>{%s}\n", line), 1);
		if (count1 != 2)
			return (printf("Parsing problem in colorline\n a cette ligne =>{%s}\n", line), 1);
	}
	if (is_start_map(line) != 1)
	{
		if (line[0] == '\n')
			return (0);
		return (printf("probleme dans le .cub les gars\n a cette ligne =>{%s}\n", line), 1);
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
		if (loop_parse_text(line, map, fd) != 0)
			return (1);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	// printf("no texture => {%s}\n", map->no_texture);
	// printf("so texture => {%s}\n", map->so_texture);
	// printf("we texture => {%s}\n", map->we_texture);
	// printf("ea texture => {%s}\n", map->ea_texture);
	// printf("ceiling color !------\n");
	// show_int_tab(map->ceiling_color);
	// printf("floor color !------\n");
	// show_int_tab(map->floor_color);
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
	// show_struct_map(map);
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
