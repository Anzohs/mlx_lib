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

static void	free_tmap(t_map *m)
{
	int	i;

	i = -1;
	while (++i < m->size.y)
		free(m->map[i]);
	free(m->map[i]);
	free(m);
}

static void	init_exit(t_game *g)
{
	g->e.sprite = (t_img){0};
	g->e.sprite.img = mlx_xpm_file_to_image(g->mlx, "exit.xpm", &g->e.sprite.pos.x, &g->e.sprite.pos.y);
	g->e.sprite.addr = mlx_get_data_addr(g->e.sprite.img, &g->e.sprite.bpp, &g->e.sprite.line_len, &g->e.sprite.endian);
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
	start_collect(g, map.c);
	event_handler(g);
	g->loop(g);
}
