/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:09:20 by maissat           #+#    #+#             */
/*   Updated: 2025/05/04 15:50:38 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void	move_player(t_player *player)
//{
//	int	speed = 2;
//	float angle_speed;
//	float cos_angle;
//	float sin_angle;

//	angle_speed = 0.1;
//	cos_angle = cos(player->angle);
//	sin_angle = sin(player->angle);

//	if (player->key_up)
//		player->y -= speed;
//	if (player->key_down)
//		player->y += speed;
//	if (player->key_left)
//		player->x -= speed;
//	if (player->key_right)
//		player->x += speed;
//}

// void move_player(t_player *player)
// {
//     float speed = 1.0;
//     float angle_speed = 0.05;
//     float cos_angle = cos(player->angle);
//     float sin_angle = sin(player->angle);

//     if (player->left_rotate)
//         player->angle -= angle_speed;
//     if (player->right_rotate)
//         player->angle += angle_speed;
//     if (player->angle > 2 * PI)
//         player->angle = 0;
//     if (player->angle < 0)
//         player->angle = 2 * PI;

//     if (player->key_up)
//     {
//         player->x += cos_angle * speed;
//         player->y += sin_angle * speed;
//     }
//     if (player->key_down)
//     {
//         player->x -= cos_angle * speed;
//         player->y -= sin_angle * speed;
//     }
//     if (player->key_left)
//     {
//         player->x += sin_angle * speed;
//         player->y -= cos_angle * speed;
//     }
//     if (player->key_right)
//     {
//         player->x -= sin_angle * speed;
//         player->y += cos_angle * speed;
//     }
// }

void	move_player(t_player *player, t_map *map)
{
	float	speed;
	float	angle_speed;
	float	cos_a;
	float	sin_a;
	float	new_x;
	float	new_y;
	float	dy;
	float	dx;

	speed = 1.0;
	angle_speed = 0.05;
	cos_a = cos(player->angle);
	sin_a = sin(player->angle);
	if (player->left_rotate)
		player->angle -= angle_speed;
	if (player->right_rotate)
		player->angle += angle_speed;
	if (player->angle > 2 * PI)
		player->angle = 0;
	if (player->angle < 0)
		player->angle = 2 * PI;
	if (player->key_up || player->key_down || player->key_left
		|| player->key_right)
	{
		dx = 0;
		dy = 0;
		if (player->key_up)
			dx += cos_a * speed, dy += sin_a * speed;
		if (player->key_down)
			dx -= cos_a * speed, dy -= sin_a * speed;
		if (player->key_left)
			dx += sin_a * speed, dy -= cos_a * speed;
		if (player->key_right)
			dx -= sin_a * speed, dy += cos_a * speed;
		new_x = player->x + dx;
		new_y = player->y;
		if (can_move(map, new_x, new_y))
			player->x = new_x;
		new_x = player->x;
		new_y = player->y + dy;
		if (can_move(map, new_x, new_y))
			player->y = new_y;
	}
}

int	key_press(int keycode, t_player *player)
{
	printf("key press: %d\n", keycode);
	if (keycode == ECHAP)
		exit(0); //ne pas oublier de free la memoire allouer !
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
