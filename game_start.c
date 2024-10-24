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
#include "minilibx_opengl/mlx.h"
#include <stdio.h> // For debug prints

static void free_tmap(t_map *m)
{
	int	i;

	i = -1;
	while (++i < m->size.y)
		free(m->map[i]);
	free(m->map[i]);
	free(m);
}

static void	write_w(t_game *g, t_map m)
{
	g->i_map.wall.img = mlx_xpm_file_to_image(g->mlx, "tiles.xpm", &g->i_map.wall.pos.x, &g->i_map.wall.pos.y);
	if (!g->i_map.wall.img)
	{
		printf("Error loading tiles.xpm\n");
		exit(1);
	}
	g->i_map.floor.img = mlx_xpm_file_to_image(g->mlx, "groun.xpm", &g->i_map.floor.pos.x, &g->i_map.wall.pos.y);
	if (!g->i_map.floor.img)
	{
		printf("Error loading groun.xpm\n");
		exit(1);
	}
	g->i_map.floor.addr = mlx_get_data_addr(g->i_map.floor.img, &g->i_map.floor.bpp, &g->i_map.floor.line_len, &g->i_map.floor.endian);
	g->i_map.wall.addr = mlx_get_data_addr(g->i_map.wall.img, &g->i_map.wall.bpp, &g->i_map.wall.line_len, &g->i_map.wall.endian);
}

static void draw_tile(t_game *g, t_img *img, int x, int y)
{
	int i, j;
	unsigned int color;

	for (i = 0; i < 32; i++)
	{
		for (j = 0; j < 32; j++)
		{
			color = *(unsigned int *)(img->addr + ((i % 16) * img->line_len + (j % 16) * (img->bpp / 8)));
			*(unsigned int *)(g->world.addr + ((y + i) * g->world.line_len + (x + j) * (g->world.bpp / 8))) = color;
		}
	}
}

static void render_map(t_game *g, t_map *m)
{
	int x, y;

	for (y = 0; y < m->size.y; y++)
	{
		for (x = 0; x < m->size.x; x++)
		{
			if (m->map[y][x] == '1')
				draw_tile(g, &g->i_map.wall, x * 32, y * 32);
			else
				draw_tile(g, &g->i_map.floor, x * 32, y * 32);
		}
	}
}

static void	init_world(t_game *g, t_vector s)
{
	g->world.img = mlx_new_image(g->mlx, s.x * 32, s.y * 32);
	if (!g->world.img)
	{
		printf("Error creating world image\n");
		exit(1);
	}
	g->world.addr = mlx_get_data_addr(g->world.img, &g->world.bpp, &g->world.line_len, &g->world.endian);
}

static void	init_cam(t_game *g, t_vector s)
{
	g->cam.img = mlx_new_image(g->mlx, s.x, s.y);
	if (!g->cam.img)
	{
		printf("Error creating cam image\n");
		exit(1);
	}
	g->cam.addr = mlx_get_data_addr(g->cam.img, &g->cam.bpp, &g->cam.line_len, &g->cam.endian);
}

static void copy_image(t_img *src, t_img *dst, t_vector src_pos, t_vector size)
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

static void update_camera(t_game *g, t_map *m)
{
	t_vector cam_pos;

	cam_pos.x = g->p.pos.x * 32 - 400;
	cam_pos.y = g->p.pos.y * 32 - 300;

	if (cam_pos.x < 0)
		cam_pos.x = 0;
	if (cam_pos.y < 0)
		cam_pos.y = 0;
	if (cam_pos.x + 800 > m->size.x * 32)
		cam_pos.x = m->size.x * 32 - 800;
	if (cam_pos.y + 600 > m->size.y * 32)
		cam_pos.y = m->size.y * 32 - 600;

	copy_image(&g->world, &g->cam, cam_pos, (t_vector){800, 600});
}

static void center_small_map(t_game *g, t_map *m)
{
	t_vector offset;

	offset.x = (800 - m->size.x * 32) / 2;
	offset.y = (600 - m->size.y * 32) / 2;

	copy_image(&g->world, &g->cam, (t_vector){0, 0}, (t_vector){m->size.x * 32, m->size.y * 32});
}

void	game_start(t_map map)
{
	t_game	*g;

	g = init_game("so_long", (t_vector){800, 600});
	if (!g)
	{
		printf("Error initializing game\n");
		exit(1);
	}
	g->p.pos = map.p_pos;
	g->e.pos = map.e_pos;
	init_world(g, map.size);
	init_cam(g, (t_vector){800, 600});
	write_w(g, map);
	render_map(g, &map);

	if (map.size.x * 32 <= 800 && map.size.y * 32 <= 600)
		center_small_map(g, &map);
	else
		update_camera(g, &map);

	mlx_put_image_to_window(g->mlx, g->win.win, g->cam.img, 0, 0);
	mlx_loop(g->mlx);
}
