/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissat <maissat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 18:48:51 by root              #+#    #+#             */
/*   Updated: 2025/04/25 17:52:33 by maissat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void fill_texture(t_map *map, char *trimmed)
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

void fill_color(t_map *map, char *str, char choice)
{
	int		i;
	int		j;
	int 	start;
	int 	color_rgb[3] = {0};
	char	*number;
		
	i = 1;
	j = 0;
	while (str[i])
	{
		if (is_numeric(str[i]))
		{
			start = i;
			while (is_numeric(str[i]))
				i++;
			number = ft_substr(str, start, i);
			color_rgb[j++] = ft_atoi(number);
		}
		i++;
	}
	j = 0;
	while (j < 3)
	{
		if (choice == 'F')
			map->floor_color[j] = color_rgb[j];
		if (choice == 'C')
			map->ceiling_color[j] = color_rgb[j];
		j++;
	}
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

int	is_color_line(char *line)
{
	if (str_in_str(line, "F"))
		return ('F');
	else if (str_in_str(line, "C"))
		return ('C');
	else
		return (0);
}

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
	char 	*trimmed;
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
				break;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
	
}


int	main(int argc, char **argv)
{
	t_map map;
	t_game game;
	
	ft_memset(&game, 0, sizeof(t_game));
	ft_memset(&map, 0, sizeof(t_map));
	if (argc != 2)
		return (printf("Usage: ./cube3d map.cub\n"), 1);
	if (check_map(argv[1], &map) == 1)
		return (1);
	printf("on arrive ici sans encombre!\n");
	game.map = &map;
	init_game(&game);
	mlx_hook(game.win, 2, 1L << 0, key_press, 	game.player);
	mlx_hook(game.win, 3, 1L << 1, key_release, game.player);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	show_struct_map(map);
	return (0);
}