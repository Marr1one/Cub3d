/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:55:46 by root              #+#    #+#             */
/*   Updated: 2025/05/26 14:58:20 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_color_line(char *line)
{
	if (str_in_str(line, "F"))
		return ('F');
	else if (str_in_str(line, "C"))
		return ('C');
	else
		return (0);
}

void	fill_rgb(char *str, int color_rgb[3])
{
	int		i;
	int		j;
	int		start;
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
			free(number);
		}
		if (str[i] == '\0')
			break ;
		i++;
	}
}

void	fill_color(t_map *map, char *str, char choice)
{
	int		j;
	int		color_rgb[3];

	color_rgb[0] = 0;
	color_rgb[1] = 0;
	color_rgb[2] = 0;
	fill_rgb(str, color_rgb);
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