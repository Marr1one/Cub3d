/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 16:42:09 by maissat           #+#    #+#             */
/*   Updated: 2025/05/31 20:22:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clear_image(t_game *game)
{
	ft_memset(game->data, 0, WIDTH * HEIGHT * (game->bbp / 8));
}

float	distance(float delta_x, float delta_y)
{
	return (sqrt(delta_x * delta_x + delta_y * delta_y));
}

float	fix_distance(float delta_x, float delta_y, t_game game)
{
	float	angle;
	float	fix_dist;

	angle = atan2(delta_y, delta_x) - game.player->angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}


void draw_rectangle(t_game *game, int x, int y, int width, int height, int color)
{
    int i, j;
    
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            put_pixel(x + j, y + i, color, game);
        }
    }
}

// Fonction pour dessiner le titre du jeu (lettres simples)
void draw_title(t_game *game)
{
    // Dessine "CUBE 3D" en gros au centre (version simple avec des rectangles)
    int start_x = WIDTH / 2 - 100;
    int start_y = HEIGHT / 4;
    
    // C
    draw_rectangle(game, start_x, start_y, 30, 5, COLOR_YELLOW);
    draw_rectangle(game, start_x, start_y, 5, 30, COLOR_YELLOW);
    draw_rectangle(game, start_x, start_y + 25, 30, 5, COLOR_YELLOW);
    
    // U
    start_x += 40;
    draw_rectangle(game, start_x, start_y, 5, 30, COLOR_YELLOW);
    draw_rectangle(game, start_x + 25, start_y, 5, 30, COLOR_YELLOW);
    draw_rectangle(game, start_x, start_y + 25, 30, 5, COLOR_YELLOW);
    
    // B
    start_x += 40;
    draw_rectangle(game, start_x, start_y, 5, 30, COLOR_YELLOW);
    draw_rectangle(game, start_x, start_y, 25, 5, COLOR_YELLOW);
    draw_rectangle(game, start_x, start_y + 12, 20, 5, COLOR_YELLOW);
    draw_rectangle(game, start_x, start_y + 25, 25, 5, COLOR_YELLOW);
    draw_rectangle(game, start_x + 20, start_y + 5, 5, 7, COLOR_YELLOW);
    draw_rectangle(game, start_x + 20, start_y + 17, 5, 8, COLOR_YELLOW);
    
    // E
    start_x += 40;
    draw_rectangle(game, start_x, start_y, 5, 30, COLOR_YELLOW);
    draw_rectangle(game, start_x, start_y, 25, 5, COLOR_YELLOW);
    draw_rectangle(game, start_x, start_y + 12, 20, 5, COLOR_YELLOW);
    draw_rectangle(game, start_x, start_y + 25, 25, 5, COLOR_YELLOW);
    
    // 3D
    start_x += 50;
    draw_rectangle(game, start_x, start_y, 25, 5, COLOR_RED);
    draw_rectangle(game, start_x, start_y + 12, 20, 5, COLOR_RED);
    draw_rectangle(game, start_x, start_y + 25, 25, 5, COLOR_RED);
    draw_rectangle(game, start_x + 20, start_y + 5, 5, 7, COLOR_RED);
    draw_rectangle(game, start_x + 20, start_y + 17, 5, 8, COLOR_RED);
    
    start_x += 40;
    draw_rectangle(game, start_x, start_y, 5, 30, COLOR_RED);
    draw_rectangle(game, start_x, start_y, 20, 5, COLOR_RED);
    draw_rectangle(game, start_x, start_y + 25, 20, 5, COLOR_RED);
    draw_rectangle(game, start_x + 15, start_y + 5, 5, 20, COLOR_RED);
}

void	draw_menu_options(t_game *game)
{
    int start_y = HEIGHT / 2 + 50;
    int option_height = 40;
    
    // Option PLAY
    if (game->menu_selection == 0)
    {
        // Surbrillance pour PLAY
        draw_rectangle(game, WIDTH/2 - 60, start_y - 5, 120, 30, COLOR_BLUE);
        // Texte PLAY (version simple)
        draw_rectangle(game, WIDTH/2 - 40, start_y, 5, 20, COLOR_WHITE); // P
        draw_rectangle(game, WIDTH/2 - 40, start_y, 15, 5, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 - 40, start_y + 10, 15, 5, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 - 30, start_y, 5, 10, COLOR_WHITE);
        
        draw_rectangle(game, WIDTH/2 - 20, start_y, 5, 20, COLOR_WHITE); // L
        draw_rectangle(game, WIDTH/2 - 20, start_y + 15, 15, 5, COLOR_WHITE);
        
        draw_rectangle(game, WIDTH/2 - 5, start_y, 10, 5, COLOR_WHITE); // A
        draw_rectangle(game, WIDTH/2 - 5, start_y, 5, 20, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 + 5, start_y, 5, 20, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 - 5, start_y + 10, 10, 5, COLOR_WHITE);
        
        draw_rectangle(game, WIDTH/2 + 15, start_y + 15, 10, 5, COLOR_WHITE); // Y
        draw_rectangle(game, WIDTH/2 + 15, start_y, 5, 10, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 + 25, start_y, 5, 10, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 + 20, start_y + 10, 5, 10, COLOR_WHITE);
    }
    else
    {
        // PLAY normal
        draw_rectangle(game, WIDTH/2 - 40, start_y, 5, 20, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 - 40, start_y, 15, 5, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 - 40, start_y + 10, 15, 5, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 - 30, start_y, 5, 10, COLOR_WHITE);
        
        draw_rectangle(game, WIDTH/2 - 20, start_y, 5, 20, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 - 20, start_y + 15, 15, 5, COLOR_WHITE);
        
        draw_rectangle(game, WIDTH/2 - 5, start_y, 10, 5, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 - 5, start_y, 5, 20, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 + 5, start_y, 5, 20, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 - 5, start_y + 10, 10, 5, COLOR_WHITE);
        
        draw_rectangle(game, WIDTH/2 + 15, start_y + 15, 10, 5, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 + 15, start_y, 5, 10, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 + 25, start_y, 5, 10, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 + 20, start_y + 10, 5, 10, COLOR_WHITE);
    }
    
    // Option EXIT
    start_y += option_height;
    if (game->menu_selection == 1)
    {
        // Surbrillance pour EXIT
        draw_rectangle(game, WIDTH/2 - 60, start_y - 5, 120, 30, COLOR_RED);
        // Texte EXIT en blanc
        draw_rectangle(game, WIDTH/2 - 30, start_y, 5, 20, COLOR_WHITE); // E
        draw_rectangle(game, WIDTH/2 - 30, start_y, 20, 5, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 - 30, start_y + 10, 15, 5, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 - 30, start_y + 15, 20, 5, COLOR_WHITE);
        
        draw_rectangle(game, WIDTH/2 - 5, start_y, 15, 5, COLOR_WHITE); // X
        draw_rectangle(game, WIDTH/2 - 5, start_y + 15, 15, 5, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2, start_y + 5, 5, 10, COLOR_WHITE);
        
        draw_rectangle(game, WIDTH/2 + 15, start_y, 5, 20, COLOR_WHITE); // I
        draw_rectangle(game, WIDTH/2 + 10, start_y, 15, 5, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 + 10, start_y + 15, 15, 5, COLOR_WHITE);
        
        draw_rectangle(game, WIDTH/2 + 30, start_y, 15, 5, COLOR_WHITE); // T
        draw_rectangle(game, WIDTH/2 + 37, start_y, 5, 20, COLOR_WHITE);
    }
    else
    {
        // EXIT normal
        draw_rectangle(game, WIDTH/2 - 30, start_y, 5, 20, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 - 30, start_y, 20, 5, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 - 30, start_y + 10, 15, 5, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 - 30, start_y + 15, 20, 5, COLOR_WHITE);
        
        draw_rectangle(game, WIDTH/2 - 5, start_y, 15, 5, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 - 5, start_y + 15, 15, 5, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2, start_y + 5, 5, 10, COLOR_WHITE);
        
        draw_rectangle(game, WIDTH/2 + 15, start_y, 5, 20, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 + 10, start_y, 15, 5, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 + 10, start_y + 15, 15, 5, COLOR_WHITE);
        
        draw_rectangle(game, WIDTH/2 + 30, start_y, 15, 5, COLOR_WHITE);
        draw_rectangle(game, WIDTH/2 + 37, start_y, 5, 20, COLOR_WHITE);
    }
}

void draw_menu(t_game *game)
{
    // Fond noir
    clear_image(game);
    
    // Titre
    draw_title(game);
    
    // Options
    draw_menu_options(game);

}


// Fonction de gestion des touches pour le menu
int menu_key_press(int keycode, t_game *game)
{
    if (keycode == 65362 || keycode == 119) // UP arrow ou W
    {
        game->menu_selection = 0; // PLAY
    }
    else if (keycode == 65364 || keycode == 115) // DOWN arrow ou S
    {
        game->menu_selection = 1; // EXIT
    }
    else if (keycode == 65293 || keycode == 32) // ENTER ou SPACE
    {
        if (game->menu_selection == 0) // PLAY sélectionné
        {
            game->game_state = GAME_STATE;
        }
        else if (game->menu_selection == 1) // EXIT sélectionné
        {
            exit(0);
        }
    }
    else if (keycode == 65307) // ESC
    {
        exit(0);
    }
    
    return (0);
}


void draw_health_bar(t_game *game)
{
    int bar_width = 20;
    int bar_height_max = HEIGHT * 0.3 - 40; // espace dispo dans l’interface
    int bar_x = 20;
    int bar_y = HEIGHT * 0.7 + 20; // début de la zone interface
    int hp_height = (game->player->hp * bar_height_max) / 100;

    int x, y;

    // Dessiner fond noir
    for (x = 0; x < bar_width; x++)
    {
        for (y = 0; y < bar_height_max; y++)
            put_pixel(bar_x + x, bar_y + y, 0x111111, game);
    }

    // Dessiner barre de vie en rouge
    for (x = 0; x < bar_width; x++)
    {
        for (y = 0; y < hp_height; y++)
            put_pixel(bar_x + x, bar_y + (bar_height_max - y), 0xFF0000, game);
    }
}

void draw_minimap_rays(t_game *game, int x_offset, int y_offset)
{
    int num_rays = 50;
    float fov = PI / 3;
    float angle_step = fov / num_rays;
    float start_angle = game->player->angle - fov / 2;

    for (int i = 0; i < 50; i++)
    {
        float ray_angle = start_angle + i * angle_step;
        float ray_x = game->player->x;
        float ray_y = game->player->y;

        int step = 0;
        int max_steps = 200;
        while (step < max_steps)
        {
            int map_x = (int)(ray_x / 64);
            int map_y = (int)(ray_y / 64);
            if (game->map->tab[map_y][map_x] == '1')
                break;

            int minimap_x = ray_x / 64 * MINIMAP_TILE + x_offset;
            int minimap_y = ray_y / 64 * MINIMAP_TILE + y_offset;
            put_pixel(minimap_x, minimap_y, 0xAAAA00, game);

            ray_x += cos(ray_angle);
            ray_y += sin(ray_angle);
            step++;
        }
    }
}

void	draw_ceiling_and_floor(t_game *game)
{
	int				x;
	int				y;
	int				floor_color;
	int				ceiling_color;

	floor_color = rgb_to_hex_int(game->map->floor_color[0],
			game->map->floor_color[1], game->map->floor_color[2]);
	ceiling_color = rgb_to_hex_int(game->map->ceiling_color[0],
			game->map->ceiling_color[1], game->map->ceiling_color[2]);
	y = 0;
	while (y < GAME_HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < GAME_HEIGHT / 2)
				put_pixel(x, y, ceiling_color, game);
			else
				put_pixel(x, y, floor_color, game);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	char	**tab = game->map->tab;
	int		i = 0, j;
	int		x_offset;
	int		y_offset;

	x_offset = WIDTH - (game->map->width * MINIMAP_TILE) - 10;
	y_offset = HEIGHT * 0.7 + 40;

	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
		{
			if (tab[i][j] == '1')
				draw_square_minimap(j, i, 0x0000FF, game, x_offset, y_offset);
			else if (tab[i][j] == '0')
				draw_square_minimap(j, i, 0xCCCCCC, game, x_offset, y_offset);
			j++;
		}
		i++;
	}
	draw_player_on_minimap(game, x_offset, y_offset);
	draw_minimap_rays(game, x_offset, y_offset);
}

void	draw_square_minimap(int map_x, int map_y, int color, t_game *game, int x_offset, int y_offset)
{
	int i, j;
	int x = map_x * MINIMAP_TILE + x_offset;
	int y = map_y * MINIMAP_TILE + y_offset;

	for (i = 0; i < MINIMAP_TILE; i++)
	{
		for (j = 0; j < MINIMAP_TILE; j++)
		{
			put_pixel(x + i, y + j, color, game);
		}
	}
}

void draw_player_on_minimap(t_game *game, int x_offset, int y_offset)
{
    int px = (int)(game->player->x / 64 * MINIMAP_TILE) + x_offset;
    int py = (int)(game->player->y / 64 * MINIMAP_TILE) + y_offset;
    int size = 5;
    int x, y;

    for (y = -size; y <= size; y++)
    {
        for (x = -size; x <= size; x++)
        {
            put_pixel(px + x, py + y, 0xFF0000, game);
        }
    }
}

void draw_interface(t_game *game)
{
    int x;
    int start_y = GAME_HEIGHT;
    int end_y = HEIGHT;
    int color = 0x000050; // Vert fonce

    while (start_y < end_y)
    {
		x = 0;
        while (x < WIDTH)
        {
            put_pixel(x, start_y, color, game);
			x++;
        }
		start_y++;
    }
}

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		fraction;
	float		start_x;
	int			i;

	if (game->game_state == MENU_STATE)
		draw_menu(game);
	else if (game->game_state == GAME_STATE)
	{
		player = game->player;
		move_player(player, game->map);
		clear_image(game);
		draw_ceiling_and_floor(game);
		draw_interface(game);
		draw_minimap(game);
		draw_health_bar(game);
		fraction = PI / 3 / WIDTH;
		start_x = player->angle - PI / 6;
		i = 0;
		while (i < WIDTH)
		{
			draw_column_textured(player, game, start_x, i);
			start_x += fraction;
			i++;
		}
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
