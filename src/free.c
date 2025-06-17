/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissat <maissat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 08:39:56 by braugust          #+#    #+#             */
/*   Updated: 2025/06/17 19:50:49 by maissat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	tab_lenght(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->tab)
	{
		while (map->tab[i])
		{
			free(map->tab[i]);
			i++;
		}
		free(map->tab);
	}
	free(map->player);
	free(map->no_texture);
	free(map->so_texture);
	free(map->we_texture);
	free(map->ea_texture);
}

void	free_texture(void *mlx, t_texture *tex)
{
	if (!tex)
		return ;
	if (tex->img)
		mlx_destroy_image(mlx, tex->img);
	free(tex);
}

void	free_game(t_game *game)
{
	if (game->no)
		free_texture(game->mlx, game->no);
	if (game->so)
		free_texture(game->mlx, game->so);
	if (game->we)
		free_texture(game->mlx, game->we);
	if (game->ea)
		free_texture(game->mlx, game->ea);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

void	free_all(t_game *game)
{
	free_game(game);
	free_map(game->map);
}
