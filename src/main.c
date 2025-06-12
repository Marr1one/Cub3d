/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissat <maissat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:48:51 by root              #+#    #+#             */
/*   Updated: 2025/06/12 19:26:33 by maissat          ###   ########.fr       */
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
	
	while (line)
	{
		printf("line => {%s}\n",line);
		if (is_color_line(line))
		{
			while (line && is_color_line(line))
			{
				choice = is_color_line(line);
				trimmed = skip_spaces(line);
				if (!is_space_line(line))
				{
					if (fill_color(map, trimmed, choice))
						return (1);
				}
				free(trimmed);
				free(line);
				line = get_next_line(fd);
			}
		}
		if (is_texture_line(line))
		{
			while (line && is_texture_line(line))
			{	
				printf("dans la boucle while textline ou space\n");
				printf("line = {%s}\n", line);
				trimmed = skip_spaces(line);
				fill_texture(map, trimmed);
				free(trimmed);
				free(line);
				line = get_next_line(fd);
			}
		}
		if (is_space_line(line))
		{
			free(line);
			line = get_next_line(fd);
		}
		if (!is_color_line(line) && !is_texture_line(line) && !is_space_line(line))
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

int	count_color_line(t_map map)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open(map.name, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		//printf("DEBUG line = > {%s}\n", line);
		if (is_color_line(line) != 0)
		{
			//printf("COLOR LINE DETECTED => {%s}\n", line);
			count++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	printf("count a la fin de color_line ! count = {%d}\n", count);
	return (count);
}

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
