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
#include "mlx/mlx.h"
#include <stdio.h> // For debug prints

static void	free_tmap(t_map *m)
{
	int	i;

	i = -1;
	while (++i < m->size.y)
		free(m->map[i]);
	free(m->map[i]);
	free(m);
}

static void	draw_tile(t_game *g, t_img *img, int x, int y)
{
	int				j;
	int				i;
	unsigned int	color;

	i = -1;
	while (++i < 32)
	{
		j = -1;
		while (++j < 32)
		{
			color = *(unsigned int *)(img->addr + ((i % 16) * img->line_len + \
				(j % 16) * (img->bpp / 8)));
			*(unsigned int *)(g->world.addr + ((y + i) * g->world.line_len + \
				(x + j) * (g->world.bpp / 8))) = color;
		}
	}
}

static void	render_map(t_game *g, t_map *m)
{
	int	y;
	int	x;

	y = -1;
	while (++y < m->size.y)
	{
		x = -1;
		while (++x < m->size.x)
		{
			if (m->map[y][x] == '1')
				draw_tile(g, &g->i_map.wall, x * 32, y * 32);
			else
				draw_tile(g, &g->i_map.floor, x * 32, y * 32);
		}
	}
}

static void	init_cam(t_game *g, t_vector s)
{
	g->cam.img = mlx_new_image(g->mlx, s.x, s.y);
	g->cam.addr = mlx_get_data_addr(g->cam.img, &g->cam.bpp, &g->cam.line_len, &g->cam.endian);
	g->cam.pos = s;
}

static void	copy_image(t_img *src, t_img *dst, t_vector src_pos, t_vector size)
{
	int x, y;
	unsigned int color;

	for (y = 0; y < size.y; y++)
	{
		for (x = 0; x < size.x; x++)
		{
			color = *(unsigned int *)(src->addr + ((src_pos.y + y) * src->line_len + (src_pos.x + x) * (src->bpp / 8)));
			*(unsigned int *)(dst->addr + (y * dst->line_len + x * (dst->bpp / 8))) = color;
		}
	}
}

static void update_camera(t_game *g)
{
	t_vector cam_pos;

	cam_pos.x = g->p.pos.x - g->win.size.x / 2;
	cam_pos.y = g->p.pos.y - g->win.size.y / 2;
	if (cam_pos.x + 800 > g->world.pos.x)
		cam_pos.x = g->world.pos.x - 800;
	if (cam_pos.y + 600 > g->world.pos.y)
		cam_pos.y = g->world.pos.y - 600;
	if (cam_pos.x < 0)
		cam_pos.x = 0;
	if (cam_pos.y < 0)
		cam_pos.y = 0;

	copy_image(&g->world, &g->cam, cam_pos, g->win.size);
}

void	game_start(t_map map)
{
	t_game	*g;

	g = init_game("so_long", (t_vector){800, 600});
	g->p.pos.x = map.p_pos.x * 32;
	g->p.pos.y = map.p_pos.y * 32;
	g->e.pos = map.e_pos;
	init_world(g, map.size);
	init_cam(g, (t_vector){800, 600});
	write_world(g, map);
	render_map(g, &map);
	update_camera(g);
	mlx_put_image_to_window(g->mlx, g->win.win, g->cam.img, 0, 0);
	mlx_loop(g->mlx);
}
