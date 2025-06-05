/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkborder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissat <maissat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:46:49 by maissat           #+#    #+#             */
/*   Updated: 2025/06/05 17:32:22 by maissat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_top_border(t_map map)
{
	int	j;

	j = 0;
	while (map.tab[0][j] && map.tab[0][j] != '\n')
	{
		while (map.tab[0][j] == ' ')
			j++;
		if (map.tab[0][j] != '1')
		{
			if (map.tab[0][j] == '\n')
				break ;
			return (printf("Error\nTop not closed\n"), 1);
		}
		j++;
	}
	return (0);
}

int	check_bottom_border(t_map map)
{
	int	j;

	j = 0;
	while (map.tab[map.height - 1][j])
	{
		while (map.tab[map.height - 1][j] == ' ')
			j++;
		if (map.tab[map.height - 1][j] != '1')
		{
			if (map.tab[map.height - 1][j] == '\n' || map.tab[map.height
				- 1][j] == '\0')
				break ;
			return (printf("Error\nBottom not closed\n"), 1);
		}
		j++;
	}
	return (0);
}

int	check_right_border(t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (map.tab[i])
	{
		j = 0;
		while (map.tab[i][j] != '\0' && map.tab[i][j] != '\n')
			j++;
		if (j > 2)
		{
			if (map.tab[i][j] == '\n' && map.tab[i][j - 1] == ' ')
			{
				j--;
				while (map.tab[i][j] == ' ')
					j--;
				if (map.tab[i][j] != '1')
					return (printf("Error\nnot close\n"), 1);
			}
		}
		i++;
	}
	return (0);
}

int	check_left_border(t_map map)
{
	int	i;
	int	j;

	i = 0;
	while (map.tab[i])
	{
		j = 0;
		while (map.tab[i][j] == ' ')
			j++;
		if (map.tab[i][j] != '1')
			return (printf("Error\nLeft border not closed\n"), 1);
		i++;
	}
	return (0);
}

int	check_zero_surroundings(t_map map, int i, int j)
{
	if (map.tab[i - 1] && (ft_strlen(map.tab[i - 1]) < j))
		return (printf("Error\nmap no closed on line %d\n", i), 1);
	if (map.tab[i + 1] && (ft_strlen(map.tab[i + 1]) < j))
		return (printf("Error\nmap no closed on line %d\n", i), 1);
	if (map.tab[i + 1] && (map.tab[i + 1][j] != '1' && map.tab[i + 1][j] != '0'
			&& is_direction(map.tab[i + 1][j]) == 0))
		return (printf("Error\nmap no closed on line %d\n", i), 1);
	if (map.tab[i - 1] && (map.tab[i - 1][j] != '1' && map.tab[i - 1][j] != '0'
			&& is_direction(map.tab[i - 1][j]) == 0))
		return (printf("Error\nmap no closed on line %d\n", i), 1);
	return (0);
}
