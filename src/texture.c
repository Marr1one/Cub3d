/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 10:40:26 by braugust          #+#    #+#             */
/*   Updated: 2025/05/29 11:42:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_column_pixel(t_texture *tex, t_game *g, int x, int y)
{
	int				d;
	int				idx;
	unsigned char	b;
	unsigned char	g_c;
	unsigned char	r_c;

	d = (y * 256) - (HEIGHT * 128) + (tex->lh * 128);
	tex->tex_y = ((d * tex->height) / tex->lh) / 256;
	if (tex->tex_y < 0)
		tex->tex_y = 0;
	if (tex->tex_y >= tex->height)
		tex->tex_y = tex->height - 1;
	idx = tex->tex_y * tex->size_line + tex->tex_x * (tex->bpp / 8);
	if (idx < 0 || idx + 2 >= tex->size_line * tex->height)
		return ;
	b = tex->data[idx];
	g_c = tex->data[idx + 1];
	r_c = tex->data[idx + 2];
	put_pixel(x, y, (r_c << 16) | (g_c << 8) | b, g);
}

void	draw_column_loop(t_texture *tex, t_game *g, int x)
{
	int	start;
	int	end;
	int	y;

	start = (HEIGHT - tex->lh) / 2;
	if (start < 0)
		start = 0;
	end = start + tex->lh;
	if (end >= HEIGHT)
		end = HEIGHT - 1;
	y = start;
	while (y < end)
	{
		draw_column_pixel(tex, g, x, y);
		y++;
	}
}

void	draw_column_textured(t_player *pl, t_game *g, float angle, int x)
{
	t_ray		ray;
	t_texture	*tex;
	float		wall_x;
	float		perp_dist;
	int			line_h;

	if (!raycast_wall(pl, g, angle, &ray))
		return ;
	wall_x = get_wall_x(&ray, pl);
	perp_dist = get_perp_dist(&ray, pl, angle);
	tex = choose_tex(g, &ray);
	tex->tex_x = get_tex_x(&ray, tex, wall_x);
	line_h = (int)((64.0f / perp_dist) * (WIDTH / 2));
	tex->lh = line_h;
	draw_column_loop(tex, g, x);
}
