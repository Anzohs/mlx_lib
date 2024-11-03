/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_player_dead.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 21:43:09 by hladeiro          #+#    #+#             */
/*   Updated: 2024/11/02 21:43:09 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static bool	check(t_area a1, t_area a2)
{
	if (a1.v1.x > a2.v2.x || a2.v1.x > a1.v2.x)
		return (false);
	if (a1.v1.y > a2.v2.y || a2.v1.y > a1.v2.y)
		return (false);
	return (true);
}

void	is_player_dead(t_game *g)
{
	int		i;
	t_area	a1;
	t_area	a2;

	i = -1;
	a2 = (t_area){(t_vector){g->p.pos.x, g->p.pos.y + 16}, \
		(t_vector){g->p.pos.x + 10, g->p.pos.y + 20}};
	while (++i < g->enemy.nb)
	{
		a1 = (t_area){(t_vector){g->enemy.enemies[i].pos.x, \
			g->enemy.enemies[i].pos.y + 10}, \
				(t_vector){g->enemy.enemies[i].pos.x + 16, \
					g->enemy.enemies[i].pos.y + 24}};
		if (g->enemy.enemies[i].is_alive)
			if (check(a1, a2))
				ft_free_g(g, 0);
	}
}
