/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: braugust <braugust@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:59:39 by braugust          #+#    #+#             */
/*   Updated: 2025/06/24 19:00:01 by braugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_text(t_map *map)
{
	if (map->no_texture)
		free(map->no_texture);
	if (map->so_texture)
		free(map->so_texture);
	if (map->ea_texture)
		free(map->ea_texture);
	if (map->we_texture)
		free(map->we_texture);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
