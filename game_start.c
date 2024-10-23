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
	int	x;
	int	y;

	g->i_map.wall.img = mlx_xpm_file_to_image(g->mlx, "", &g->i_map.wall.pos.x, &g->i_map.wall.pos.y);
	g->i_map.floor.img = mlx_xpm_file_to_image(g->mlx, "", &g->i_map.floor.pos.x, &g->i_map.wall.pos.y);
	g->i_map.floor.addr = mlx_get_data_addr(g->mlx, &g->i_map.floor.bpp, &g->i_map.floor.line_len, &g->i_map.floor.endian);
	g->i_map.wall.addr = mlx_get_data_addr(g->mlx, &g->i_map.wall.bpp, &g->i_map.wall.line_len, &g->i_map.wall.endian);
}

static void	init_world(t_game *g, t_vector s)
{
	if (s.x < 800 || s.y < 600)
	{
		s.x = 800;
		s.y = 600;
	}
	g->world.img = mlx_new_image(g->mlx, s.x, s.y);
	g->world.addr = mlx_get_data_addr(g->mlx, &g->world.bpp, &g->world.line_len, &g->world.endian);
}

void	game_start(t_map map)
{
	t_game	*g;
	t_img	w;

	g = init_game("so_long", (t_vector){800, 600});
	g->p.pos = map.p_pos;
	g->e.pos = map.e_pos;
	init_world(g, map.size);
}
