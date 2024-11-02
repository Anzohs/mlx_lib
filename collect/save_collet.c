/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_collet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:56:05 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/31 21:56:06 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	save_collect(t_game *g, t_map *map)
{
	int	i;

	i = -1;
	while (++i < map->c)
	{
		g->c.c[i].pos.x = map->c_pos[i].x * 32;
		g->c.c[i].pos.y = map->c_pos[i].y * 32;
		g->c.c[i].current = (t_img){0};
		g->c.c[i].current.pos = (t_vector){16, 16};
		g->c.c[i].nb_frame = 6;
		g->c.c[i].frame = 0;
		g->c.c[i].collected = false;
		g->c.c[i].is_colliding = is_colliding;
	}
}
