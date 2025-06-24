/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:35:24 by braugust          #+#    #+#             */
/*   Updated: 2025/06/24 18:35:58 by braugust         ###   ########.fr       */
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

void	cleanup_remaining_lines(char **line, int fd)
{
	while (*line)
	{
		free(*line);
		*line = get_next_line(fd);
	}
}

int	process_color_lines(char **line, t_map *map, int fd)
{
	char	choice;
	char	*trimmed;

	while (*line && is_color_line(*line))
	{
		choice = is_color_line(*line);
		trimmed = skip_spaces(*line);
		if (!is_space_line(*line))
		{
			if (fill_color(map, trimmed, choice))
			{
				free(trimmed);
				cleanup_remaining_lines(line, fd);
				return (1);
			}
		}
		free(trimmed);
		free(*line);
		*line = get_next_line(fd);
	}
	return (0);
}
