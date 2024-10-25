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
#include <stdio.h> // For debug prints
#include <X11/keysym.h>
#include <X11/X.h>

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
			if (color != 0xFF000000)
				*(unsigned int *)(w->addr + ((pos.y + y) * w->line_len + (pos.x + x) * (w->bpp / 8))) = color;
		}
	}
}

static void	draw_p(t_game *g)
{
	int	src_x = g->p.anim.frame * g->p.sprite.pos.x;
	int	src_y = g->p.anim.row * g->p.sprite.pos.y;
	int	x;
	int	y = -1;
	unsigned int color;

	if (g->p.current.img)
		mlx_destroy_image(g->mlx, g->p.current.img);
	g->p.current.img = mlx_new_image(g->mlx, g->p.sprite.pos.x, g->p.sprite.pos.y);
	g->p.current.addr = mlx_get_data_addr(g->p.current.img, &g->p.current.bpp, &g->p.current.line_len, &g->p.current.endian);

	while (++y < g->p.sprite.pos.y)
	{
		x = -1;
		while (++x < g->p.sprite.pos.x)
		{
			color = *(unsigned int *)(g->p.sprite.addr + ((src_y + y) * g->p.sprite.line_len + (src_x + x) * (g->p.sprite.bpp / 8)));
			*(unsigned int *)(g->p.current.addr + (y * g->p.current.line_len + x * (g->p.current.bpp / 8))) = color;
		}
	}

	player_to_world(&g->world, &g->p.current, g->p.pos);
}

static	void	player_start(t_game *g)
{
	g->p.ar = (t_area){g->p.pos, (t_vector){16, 32}};
	g->p.score = 0;
	g->p.health = 3;
	g->p.walk = 0;
	g->p.sprite = (t_img){0};
	g->p.sprite.img = mlx_xpm_file_to_image(g->mlx, "character_walk.xpm", &g->p.sprite.pos.x, &g->p.sprite.pos.y);
	g->p.sprite.addr = mlx_get_data_addr(g->p.sprite.img, &g->p.sprite.bpp, &g->p.sprite.line_len, &g->p.sprite.endian);
	g->p.sprite.pos.x = 16;
	g->p.sprite.pos.y = 32;
	g->p.anim = (t_sprite){0};
	g->p.anim.frame = 0;
	g->p.anim.nb_frame = 4;
	g->p.anim.row = 0;
	g->p.anim.animating = false;
	g->p.current = (t_img){0};
}

static int	animate(t_game *g)
{
	static int	delay;

	if (++delay < 1000)
		return 0;
	delay = 0;

	if (g->p.anim.animating)
		g->p.anim.frame = (g->p.anim.frame + 1) % g->p.anim.nb_frame;
	else
		g->p.anim.frame = 0;

	if (g->p.anim.down && (g->map->map[(g->p.pos.y + 5) / 32][g->p.pos.x / 32] != '1'))
		g->p.pos.y = (g->p.pos.y + 5 < g->world.pos.y - g->p.sprite.pos.y) ? g->p.pos.y + 5 : g->p.pos.y;
	if (g->p.anim.up && (g->map->map[(g->p.pos.y - 5) / 32][g->p.pos.x / 32] != '1'))
		g->p.pos.y = (g->p.pos.y - 5 >= 0) ? g->p.pos.y - 5 : g->p.pos.y;
	if (g->p.anim.right && (g->map->map[g->p.pos.y / 32][(g->p.pos.x + 5) / 32] != '1'))
		g->p.pos.x = (g->p.pos.x + 5 < g->world.pos.x - g->p.sprite.pos.x) ? g->p.pos.x + 5 : g->p.pos.x;
	if (g->p.anim.left && (g->map->map[g->p.pos.y / 32][(g->p.pos.x - 5) / 32] != '1'))
		g->p.pos.x = (g->p.pos.x - 5 >= 0) ? g->p.pos.x - 5 : g->p.pos.x;

	g->p.anim.animating = (g->p.anim.down || g->p.anim.up || g->p.anim.right || g->p.anim.left);

	render_map(g, g->map); // Redraw the map
	draw_p(g); // Draw the player
	update_cam(g);
	mlx_put_image_to_window(g->mlx, g->win.win, g->cam.img, 0, 0);
	return 0;
}

static int keypress(int key, t_game *g)
{
	if (key == XK_Up || key == XK_w)
	{
		g->p.anim.row = 2;
		g->p.anim.up = 1;
	}
	else if (key == XK_Down || key == XK_s)
	{
		g->p.anim.row = 0;
		g->p.anim.down = 1;
	}
	else if (key == XK_Left || key == XK_a)
	{
		g->p.anim.row = 3;
		g->p.anim.left = 1;
	}
	else if (key == XK_Right || key == XK_d)
	{
		g->p.anim.row = 1;
		g->p.anim.right = 1;
	}
	if (key == XK_Right || key == XK_d || key == XK_Up || key == XK_w || key == XK_Down || key == XK_s || key == XK_Left || key == XK_a)
		g->p.anim.animating = true;
	return (1);
}

static int	keyrelease(int key, t_game *g)
{
	if (key == XK_Up || key == XK_w)
		g->p.anim.up = 0;
	else if (key == XK_Down || key == XK_s)
		g->p.anim.down = 0;
	else if (key == XK_Left || key == XK_a)
		g->p.anim.left = 0;
	else if (key == XK_Right || key == XK_d)
		g->p.anim.right = 0;

	if (!g->p.anim.down && !g->p.anim.up && !g->p.anim.right && !g->p.anim.left)
	{
		g->p.anim.animating = false;
		g->p.anim.frame = 0;
	}
	return (0);
}

static void	loop(t_game *g)
{
	mlx_hook(g->win.win, 2, 1L<<0, keypress, g);
	mlx_hook(g->win.win, 3, 1L<<1, keyrelease, g);
	mlx_loop_hook(g->mlx, animate, g);
	mlx_loop(g->mlx);
}

void	game_start(t_map map)
{
	t_game	*g;

	g = init_game("so_long", (t_vector){800, 600});
	g->p.pos.x = map.p_pos.x * 32;
	g->p.pos.y = map.p_pos.y * 32;
	g->e.pos = map.e_pos;
	g->map = &map;
	g->loop = loop;
	init_world(g, (*g).map->size);
	init_cam(g, (t_vector){800, 600});
	write_world(g, *g->map);
	player_start(g);
	render_map(g, g->map);
	draw_p(g);
	update_cam(g);
	mlx_put_image_to_window(g->mlx, g->win.win, g->cam.img, 0, 0);
	g->loop(g);
}
