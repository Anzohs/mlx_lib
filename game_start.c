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

static int	game_loop(t_game *g)
{
	return (update_game(g, g->dt()));
}

void	game_start(t_map map)
{
	t_game	*g;

	g = init_game("so_long", (t_vector){800, 600}, &map);
	g->p.pos = (t_vector){map.p_pos.x * 32, map.p_pos.y * 32};
	g->e.pos = map.e_pos;
	g->animate = game_loop;
	init_world(g, map.size);
	init_cam(g, (t_vector){800, 600});
	write_world(g);
	player_start(g);
	init_exit(g);
	start_collect(g, map.c);
	init_enemy(g, map.x);
	event_handler(g);
	g->loop(g);
}
