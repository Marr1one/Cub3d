/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:29:12 by maissat           #+#    #+#             */
/*   Updated: 2025/05/29 11:40:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_on_map(t_player *player, t_map *map, float dx, float dy)
{
	float	new_x;
	float	new_y;

	new_x = player->x + dx;
	new_y = player->y;
	if (can_move(map, new_x, new_y))
		player->x = new_x;
	new_x = player->x;
	new_y = player->y + dy;
	if (can_move(map, new_x, new_y))
		player->y = new_y;
}

void	move_player(t_player *player, t_map *map)
{
	float	speed;

	speed = 2;
	rotate_player(player);
	if (player->key_up || player->key_down || player->key_left
		|| player->key_right)
	{
		get_player_move_delta(player, speed);
		move_on_map(player, map, player->dx, player->dy);
	}
}

int	key_press(int keycode, t_player *player)
{
	if (keycode == ECHAP)
		exit(0);
	if (keycode == W)
		player->key_up = 1;
	if (keycode == S)
		player->key_down = 1;
	if (keycode == A)
		player->key_left = 1;
	if (keycode == D)
		player->key_right = 1;
	if (keycode == ROT_LEFT)
		player->left_rotate = 1;
	if (keycode == ROT_RIGHT)
		player->right_rotate = 1;
	return (0);
}

int	key_release(int keycode, t_player *player)
{
	if (keycode == W)
		player->key_up = 0;
	if (keycode == S)
		player->key_down = 0;
	if (keycode == A)
		player->key_left = 0;
	if (keycode == D)
		player->key_right = 0;
	if (keycode == ROT_LEFT)
		player->left_rotate = 0;
	if (keycode == ROT_RIGHT)
		player->right_rotate = 0;
	return (0);
}
