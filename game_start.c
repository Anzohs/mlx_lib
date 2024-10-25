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
	if (g->p.current.img)
		mlx_destroy_image(g->mlx, g->p.current.img);
	g->p.current.img = mlx_new_image(g->mlx, g->p.sprite.pos.x, g->p.sprite.pos.y);
	g->p.current.addr = mlx_get_data_addr(g->p.current.img, &g->p.current.bpp, &g->p.current.line_len, &g->p.current.endian);
	player_to_world(&g->world, &g->p.sprite, g->p.pos);
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
	g->p.anim.frame = 0;
	g->p.anim.nb_frame = 4;
	g->p.anim.row = 0;
	g->p.anim.animating = false;
	g->p.current = (t_img){0};
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
	player_start(g);
	draw_p(g);
	update_cam(g);
	mlx_put_image_to_window(g->mlx, g->win.win, g->cam.img, 0, 0);
	g->loop(g);
}
