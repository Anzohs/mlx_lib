/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:35:06 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/23 21:35:08 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/game.h"
#include "inc/structs.h"
#include "mlx/mlx.h"
#include <stdio.h>
#include <sys/time.h>
#include <time.h>


#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_UP 126
#define KEY_DOWN 125
#define KEY_LEFT 123
#define KEY_RIGHT 124
#define KEY_ESC 53
#define FPS 60
#define FRAME_DURATION (1000000 / FPS) 


static void	free_tmap(t_map *m)
{
	int	i;

	i = -1;
	while (++i < m->size.y)
		free(m->map[i]);
	free(m->map[i]);
	free(m);
}

static void	player_to_world(t_img *w, t_img *p, t_vector pos)
{
	int				y;
	int				x;
	unsigned int	color;

	y = -1;
	while(++y < p->pos.y)
	{
		x = -1;
		while (++x < p->pos.x)
		{
			color = *(unsigned int *)(p->addr + (y * p->line_len + x * (p->bpp / 8)));
			if ((color & 0x00FFFFFF) != 0)
				*(unsigned int *)(w->addr + ((pos.y + y) * w->line_len + (pos.x + x) * (w->bpp / 8))) = color;
		}
	}
}

static void	draw_p(t_game *g)
{
	int	src_x = g->p.anim.frame * g->p.sprite.pos.x;
	int	src_y = g->p.anim.row * g->p.sprite.pos.y;
	int	x;
	int	y;
	unsigned int color;

	if (g->p.current.img)
		mlx_destroy_image(g->mlx, g->p.current.img);

	g->p.current.img = mlx_new_image(g->mlx, g->p.sprite.pos.x, g->p.sprite.pos.y);
	g->p.current.addr = mlx_get_data_addr(g->p.current.img, &g->p.current.bpp,
		&g->p.current.line_len, &g->p.current.endian);
	g->p.current.pos = g->p.sprite.pos;  // Add this line

	y = -1;
	while (++y < g->p.sprite.pos.y)
	{
		x = -1;
		while (++x < g->p.sprite.pos.x)
		{
			color = *(unsigned int *)(g->p.sprite.addr + ((src_y + y) * g->p.sprite.line_len + (src_x + x) * (g->p.sprite.bpp / 8)));
			if (color != 0xFF000000)
				*(unsigned int *)(g->p.current.addr + (y * g->p.current.line_len + x * (g->p.current.bpp / 8))) = color;
		}
	}

	// Draw to world
	player_to_world(&g->world, &g->p.current, g->p.pos);
}

static	void	player_start(t_game *g)
{
	g->p.ar = (t_area){g->p.pos, (t_vector){16, 32}};
	g->p.score = 0;
	g->p.health = 3;
	g->p.walk = 0;
	g->p.sprite = (t_img){0};
	g->p.sprite.img = mlx_xpm_file_to_image(g->mlx, "character_walk.xpm",
		&g->p.sprite.pos.x, &g->p.sprite.pos.y);
	g->p.sprite.addr = mlx_get_data_addr(g->p.sprite.img, &g->p.sprite.bpp,
		&g->p.sprite.line_len, &g->p.sprite.endian);
	g->p.sprite.pos.x = 16;
	g->p.sprite.pos.y = 32;
	g->p.anim = (t_sprite){0};
	g->p.anim.frame = 0;
	g->p.anim.nb_frame = 4;
	g->p.anim.row = 0;
	g->p.anim.animating = false;
	g->p.anim.up = 0;
	g->p.anim.down = 0;
	g->p.anim.left = 0;
	g->p.anim.right = 0;
	g->p.current = (t_img){0};
}

static bool	is_colliding(t_area a1, t_area a2)
{
	return (a2.v2.x > a1.v1.x && a2.v1.x < a1.v2.x
		&& a2.v2.y > a1.v1.y && a2.v1.y < a1.v2.y);
}

static int	animate(t_game *g)
{
	static int	delay = 0;
	static clock_t last_frame_time;
    clock_t current_time = clock();
	int new_x = g->p.pos.x;
    int new_y = g->p.pos.y;


	if (g->p.anim.animating)
	{
		if ((current_time - last_frame_time) > (CLOCKS_PER_SEC / 10))
		{
			g->p.anim.frame = (g->p.anim.frame + 1) % g->p.anim.nb_frame;
			last_frame_time = current_time;
		}
	}
	else
		g->p.anim.frame = 0;
	
	ft_putnbr_fd(g->p.anim.frame, 1);
	if (g->p.anim.down)
    {
        new_y += 5;
        if (g->map->map[(new_y + 31) / 32][new_x / 32] == '1' || // Bottom-left corner
            g->map->map[(new_y + 31) / 32][(new_x + 15) / 32] == '1' || // Bottom-right corner
            g->map->map[(new_y + 32 - 1) / 32][new_x / 32] == '1' || // Bottom-left corner
            g->map->map[(new_y + 32 - 1) / 32][(new_x + 16 - 1) / 32] == '1') // Bottom-right corner
            new_y = g->p.pos.y;
    }
    else if (g->p.anim.up)
    {
        new_y -= 5;
        if (g->map->map[new_y / 32][new_x / 32] == '1' || // Top-left corner
            g->map->map[new_y / 32][(new_x + 15) / 32] == '1' || // Top-right corner
            g->map->map[new_y / 32][new_x / 32] == '1' || // Top-left corner
            g->map->map[new_y / 32][(new_x + 16 - 1) / 32] == '1') // Top-right corner
            new_y = g->p.pos.y;
    }
    else if (g->p.anim.right)
    {
        new_x += 5;
        if (g->map->map[new_y / 32][(new_x + 15) / 32] == '1' || // Top-right corner
            g->map->map[(new_y + 31) / 32][(new_x + 15) / 32] == '1' || // Bottom-right corner
            g->map->map[new_y / 32][(new_x + 16 - 1) / 32] == '1' || // Top-right corner
            g->map->map[(new_y + 32 - 1) / 32][(new_x + 16 - 1) / 32] == '1') // Bottom-right corner
            new_x = g->p.pos.x;
    }
    else if (g->p.anim.left)
    {
        new_x -= 5;
        if (g->map->map[new_y / 32][new_x / 32] == '1' || // Top-left corner
            g->map->map[(new_y + 31) / 32][new_x / 32] == '1' || // Bottom-left corner
            g->map->map[new_y / 32][new_x / 32] == '1' || // Top-left corner
            g->map->map[(new_y + 32 - 1) / 32][new_x / 32] == '1') // Bottom-left corner
            new_x = g->p.pos.x;
    }

    g->p.pos.x = new_x;
    g->p.pos.y = new_y;


	//g->p.anim.animating = (g->p.anim.down || g->p.anim.up || g->p.anim.right || g->p.anim.left);

	render_map(g, g->map);
	draw_p(g);
	update_cam(g);
	mlx_put_image_to_window(g->mlx, g->win.win, g->cam.img, 0, 0);
	return (0);
}



static int	keypress(int key, t_game *g)
{
	if (key == KEY_ESC)
		exit_t(g);
	else if (key == 119)
	{
		g->p.anim.row = 2;
		g->p.anim.up = 1;
		g->p.anim.animating = true;
	}
	else if (key == 115)
	{
		g->p.anim.row = 0;
		g->p.anim.down = 1;
		g->p.anim.animating = true;
	}
	else if (key == 97)
	{
		g->p.anim.row = 3;
		g->p.anim.left = 1;
		g->p.anim.animating = true;
	}
	else if (key == 65363 || key == 100)
	{
		g->p.anim.row = 1;
		g->p.anim.right = 1;
		g->p.anim.animating = true;
	}
	return (0);
}

static int	keyrelease(int key, t_game *g)
{
	if (key == KEY_UP || key == 119)
		g->p.anim.up = 0;
	else if (key == KEY_DOWN || key == 115)
		g->p.anim.down = 0;
	else if (key == KEY_LEFT || key == 97)
		g->p.anim.left = 0;
	else if (key == 65363 || key == 100)
		g->p.anim.right = 0;

	if (!g->p.anim.down && !g->p.anim.up && !g->p.anim.right && !g->p.anim.left)
	{
		g->p.anim.animating = false;
		g->p.anim.frame = 0;
	}
	return (0);
}

static int	update(t_game *g)
{
	static struct timeval last_time;
    struct timeval current_time;
    long elapsed_time;

    // Get the current time
    gettimeofday(&current_time, NULL);

    // Calculate the elapsed time since the last frame
    elapsed_time = (current_time.tv_sec - last_time.tv_sec) * 1000000 + (current_time.tv_usec - last_time.tv_usec);

    // If the elapsed time is less than the frame duration, sleep for the remaining time
    if (elapsed_time < FRAME_DURATION)
    {
        usleep(FRAME_DURATION - elapsed_time);
    }

    // Update the last time to the current time
    gettimeofday(&last_time, NULL);
	animate(g);
	return (0);
}

void	game_start(t_map map)
{
	t_game	*g;

	g = init_game("so_long", (t_vector){800, 600});
	g->p.pos.x = map.p_pos.x * 32;
	g->p.pos.y = map.p_pos.y * 32;
	g->e.pos = map.e_pos;
	g->map = &map;
	g->frame_per_time = 0;
	init_world(g, map.size);
	init_cam(g, (t_vector){800, 600});
	write_world(g, map);
	player_start(g);
	render_map(g, g->map);
	draw_p(g);
	update_cam(g);
	mlx_put_image_to_window(g->mlx, g->win.win, g->cam.img, 0, 0);

	// Set up event hooks
	mlx_hook(g->win.win, 3, 1L<<1, keyrelease, g);
	mlx_hook(g->win.win, 2, 1L<<0, keypress, g);
	mlx_loop_hook(g->mlx, update, g);
	mlx_loop(g->mlx);
}
