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

#include "inc/collectable.h"
#include "inc/game.h"

static void	free_tmap(t_map *m)
{
	int	i;

	i = -1;
	while (++i < m->size.y)
		free(m->map[i]);
	free(m->map[i]);
	free(m);
}

static void colect_img(t_game *g, t_col *c)
{
	c->sprite.img = mlx_xpm_file_to_image(g->mlx, "cristal.xpm", \
		&c->sprite.pos.x, &c->sprite.pos.y);
	c->sprite.addr = mlx_get_data_addr(c->sprite.img, &c->sprite.bpp, \
		&c->sprite.line_len, &c->sprite.endian);
	c->sprite.pos = (t_vector){16, 16};
}

static void	collected(t_game *g, t_col *c)
{
	c->col.img = mlx_xpm_file_to_image(g->mlx, "crystal_collected.xpm", \
		&c->col.pos.x, &c->col.pos.y);
	c->col.addr = mlx_get_data_addr(c->col.img, &c->col.bpp, \
		&c->col.line_len, &c->col.endian);
	c->col.pos = (t_vector){16, 16};
}

static void	save_colect(t_game *g, t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->c)
	{
		g->c.c[i].pos.x = map->c_pos[i].x * 32;
		g->c.c[i].pos.y = map->c_pos[i].y * 32;
		g->c.c[i].current = (t_img) {0};
		g->c.c[i].current.pos = (t_vector) {16, 16};
		g->c.c[i].nb_frame = 6;
		g->c.c[i].collected = false;
		g->c.c[i].is_colliding = is_colliding;
	}
}

static void	start_colect(t_game *g, int n)
{
	int	i;

	i = -1;
	g->c.c = (t_colectable *)ft_calloc(n + 1, sizeof(t_colectable));
	colect_img(g, &g->c);
	collected(g, &g->c);
	while (++i < n)
		g->c.c[i] = (t_colectable){0};
}

static int	game_loop(t_game *g)
{
	return (update_game(g, g->dt()));
}

void	game_start(t_map map)
{
	t_game	*g;

	g = init_game("so_long", (t_vector){800, 600});
	g->p.pos.x = map.p_pos.x * 32;
	g->p.pos.y = map.p_pos.y * 32;
	g->e.pos = map.e_pos;
	g->map = &map;
	g->animate = game_loop;
	init_world(g, map.size);
	init_cam(g, (t_vector){800, 600});
	write_world(g, map);
	player_start(g);
	ft_putnbr_fd(map.c, 1);
	start_colect(g, map.c);
	save_colect(g, &map);
	event_handler(g);
	g->loop(g);
}
