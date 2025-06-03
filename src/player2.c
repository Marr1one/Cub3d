/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maissat <maissat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 12:44:51 by braugust          #+#    #+#             */
/*   Updated: 2025/06/03 15:34:22 by maissat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_player(t_player *player)
{
	float	angle_speed;

	angle_speed = 0.03;
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
}

void	move_delta_up_down(t_player *player, float speed)
{
	float	cos_a;
	float	sin_a;

	cos_a = cos(player->angle);
	sin_a = sin(player->angle);
	if (player->key_up)
	{
		player->dx += cos_a * speed;
		player->dy += sin_a * speed;
	}
	if (player->key_down)
	{
		player->dx -= cos_a * speed;
		player->dy -= sin_a * speed;
	}
}

void	move_delta_left_right(t_player *player, float speed)
{
	float	cos_a;
	float	sin_a;

	cos_a = cos(player->angle);
	sin_a = sin(player->angle);
	if (player->key_left)
	{
		player->dx += sin_a * speed;
		player->dy -= cos_a * speed;
	}
	if (player->key_right)
	{
		player->dx -= sin_a * speed;
		player->dy += cos_a * speed;
	}
}

void	get_player_move_delta(t_player *player, float speed)
{
	player->dx = 0;
	player->dy = 0;
	move_delta_up_down(player, speed);
	move_delta_left_right(player, speed);
}
