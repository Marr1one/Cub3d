/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissat <maissat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:10:30 by maissat           #+#    #+#             */
/*   Updated: 2025/04/19 17:54:35 by maissat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_tab(t_map *map)
{
	char	*line;
	char	**tab;
	int		fd;
	int		i;
	int		j;

	tab = malloc(sizeof(char *) * (map->height + 1));
	if (!tab)
		return ;
	map->tab = tab;
	fd = open(map->name, O_RDONLY);
	if (fd < 0)
		return ;
	i = 0;
	j = 0;
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] == ' ')
			i++;
		if (line[i] && line[i] == '1')
		{
			map->tab[j++] = ft_strduptab(line, map);
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	map->tab[j] = NULL;
	close(fd);
}