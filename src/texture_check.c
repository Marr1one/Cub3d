/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:57:20 by root              #+#    #+#             */
/*   Updated: 2025/05/27 10:29:07 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fill_texture(t_map *map, char *trimmed)
{
	if (ft_strncmp(trimmed, "NO.", 3) == 0)
	{
		map->no_texture = ft_strduptext(trimmed + 2);
	}
	if (ft_strncmp(trimmed, "SO.", 3) == 0)
		map->so_texture = ft_strduptext(trimmed + 2);
	if (ft_strncmp(trimmed, "WE.", 3) == 0)
		map->we_texture = ft_strduptext(trimmed + 2);
	if (ft_strncmp(trimmed, "EA.", 3) == 0)
		map->ea_texture = ft_strduptext(trimmed + 2);
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
