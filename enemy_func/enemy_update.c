/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:35:19 by hladeiro          #+#    #+#             */
/*   Updated: 2024/11/02 20:35:19 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static bool	check_pos(t_area a1, t_area a2)
{
	if (a1.v1.x > a2.v2.x || a2.v1.x > a1.v2.x)
		return (false);
	if (a1.v1.y > a2.v2.y || a2.v1.y > a1.v2.y)
		return (false);
	return (true);
}

static t_area	check_pside(t_player *p)
{
	if (p->side == 0)
		return (((t_area){(t_vector){p->pos.x, p->pos.y + 16}, \
			(t_vector){p->pos.x + 16, p->pos.y + 20}}));
	if (p->side == 1)
		return ((t_area){(t_vector){p->pos.x + 8, p->pos.y}, \
			(t_vector){p->pos.x + 32, p->pos.y + 32}});
	if (p->side == 2)
		return ((t_area){(t_vector){p->pos.x, p->pos.y - 30}, \
			(t_vector){p->pos.x + 32, p->pos.y}});
	return ((t_area){(t_vector){p->pos.x - 10, p->pos.y}, \
		(t_vector){p->pos.x, p->pos.y + 32}});
}

static bool	is_dead(t_enemy *e, t_player *p)
{
	if (!p->anim.sword_anim)
		return (false);
	return (check_pos((t_area){e->pos, \
		(t_vector){e->pos.x + 24, e->pos.y + 30}}, \
			check_pside(p)));
}

void	update_enemy(t_game *g, double dt)
{
	int		i;

	i = -1;
	(void)dt;
	while (++i < g->map->x)
	{
		if (g->enemy.enemies[i].is_alive && is_dead(&g->enemy.enemies[i], &g->p))
		{
			ft_putstr_fd("update_enemy", 2);
			g->enemy.enemies[i].is_alive = false;
			g->enemy.enemies[i].frame = 0;
		}
		/*else
		{
			enemy_move(&g->enemy.enemies[i], g->map, dt);
			animation_up(&g->enemy.enemies[i], dt);
			}*/
	}
}
