/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:55:46 by root              #+#    #+#             */
/*   Updated: 2025/06/24 17:22:56 by braugust         ###   ########.fr       */
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

int	extract_rgb_number(char *str, int *pos, int *color_value)
{
	int		start;
	char	*number;
	int		numero;

	if (!is_numeric(str[*pos]))
		return (printf("caracter not coform\n"), 1);
	start = *pos;
	while (is_numeric(str[*pos]))
		(*pos)++;
	if (str[*pos] != ',' && str[*pos] != '\n' && str[*pos] != '\0')
		return (printf("DEBUG => autre chose que ,entre les chiffres,=> {%c}\n",
				str[*pos]), 1);
	number = ft_substr(str, start, *pos);
	numero = ft_atoi(number);
	free(number);
	if (numero < 0 || numero > 255)
		return (printf("RGB not in range 0-256\n"), 1);
	*color_value = numero;
	return (0);
}

int	fill_rgb(char *str, int color_rgb[3])
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (str[i])
	{
		if (extract_rgb_number(str, &i, &color_rgb[j++]) != 0)
			return (1);
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
