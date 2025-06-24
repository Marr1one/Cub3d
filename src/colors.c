/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:55:46 by root              #+#    #+#             */
/*   Updated: 2025/06/24 16:25:25 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_color_line(char *line)
{
	int	i;

	i = 0;
	while (line && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == 'F')
		return ('F');
	else if (line[i] == 'C')
		return ('C');
	else
		return (0);
}

int	fill_rgb(char *str, int color_rgb[3])
{
	int		i;
	int		j;
	int		start;
	char	*number;
	int		numero;

	i = 1;
	j = 0;
	while (str[i])
	{
		if (is_numeric(str[i]))
		{
			start = i;
			while (is_numeric(str[i]))
				i++;
			if (str[i] != ',')
			{
				if (str[i] != '\n' && str[i] != '\0')
					return (printf("DEBUG => autre chose que ,entre les chiffres, => {%c}\n", str[i]), 1);
			}
			number = ft_substr(str, start, i);
			numero = ft_atoi(number);
			if (numero < 0 || numero > 255)
				return (printf("RGB not in range 0-256\n"), 1);
			color_rgb[j++] = numero;
			free(number);
		}
		else if (!is_numeric(str[i]))
			return (printf("caracter not coform\n"), 1);
		if (str[i] == '\0')
			break ;
		i++;
	}
	return (0);
}

int	fill_color(t_map *map, char *str, char choice)
{
	int	j;
	int	color_rgb[3];

	printf("in fill color => line = {%s}\n", str);
	color_rgb[0] = 0;
	color_rgb[1] = 0;
	color_rgb[2] = 0;
	if (fill_rgb(str, color_rgb) == 1)
		return (1);
	j = 0;
	while (j < 3)
	{
		if (choice == 'F')
			map->floor_color[j] = color_rgb[j];
		if (choice == 'C')
			map->ceiling_color[j] = color_rgb[j];
		j++;
	}
	return (0);
}
