/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissat <maissat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:10:30 by maissat           #+#    #+#             */
/*   Updated: 2025/04/25 15:39:11 by maissat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void create_tab(t_map *map)
{
    char *line;
    int map_started;
    char **tab;
    int fd;
    int i;
    int j;

    map_started = 0;
    tab = malloc(sizeof(char *) * (map->height + 1));
    if (!tab)
        return;
    map->tab = tab;
    fd = open(map->name, O_RDONLY);
    if (fd < 0)
        return;
    i = 0;
    j = 0;
    line = get_next_line(fd);
    while (line)
    {
        i = 0;
        while (line[i] && line[i] == ' ')
            i++;
        if (line[i] == '1')
        {
            map_started = 1;
            map->tab[j++] = ft_strduptab(line, map);
        }
        else if (map_started && (line[i] == '\0' || line[i] == '\n'))
        {
            free(line);
            break;
        }
        
        free(line);
        line = get_next_line(fd);
    }
    map->tab[j] = NULL;
    close(fd);
}