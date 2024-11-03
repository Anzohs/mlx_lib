/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 00:54:58 by hladeiro          #+#    #+#             */
/*   Updated: 2024/11/03 00:54:59 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static int	get_dit(int dx, int dy, int rd, t_map *m)
{
	if (rd == 0 && m->map[(dy - 1) / 32][dx / 32] != 1)
		return (3);
	else if (rd == 1 && m->map[(dy + 24) / 32][dx / 32])
		return (0);
	else if (rd == 2 && m->map[dy / 32][(dx - 1) / 32] != '1')
		return (2);
	else if (rd == 3 && m->map[dy / 32][(dx + 24) / 32] != 1)
		return (1);
	return (5);
}

void	enemy_move(t_enemy *e, t_map *m, double dt)
{
	int	dir;

	dir = get_dit(e->pos.x, e->pos.y, rand() % 4, m);
	if (dir == 5)
		return ;
	e->dir = dir;
	if (e->dir == 3)
		e->pos.y -= (3 * dt) + 1;
	else if (e->dir == 0)
		e->pos.y += (3 * dt) + 1;
	else if (e->dir == 2)
		e->pos.x -= (3 * dt) + 1;
	else
		e->pos.x += (3 * dt) + 1;
}
