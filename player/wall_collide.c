/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collide.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:49:45 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/25 22:49:46 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static void	collide_left(t_player *p, t_map *map, int x, int y)
{
	if (!(map->map[y / 32][x / 32] == '1' || \
			map->map[(y + 31) / 32][x / 32] == '1' || \
			map->map[y / 32][x / 32] == '1' || \
			map->map[(y + 32 - 1) / 32][x / 32] == '1'))
	{
		p->pos.x = x;
		p->walk++;
	}
}

static void	collide_right(t_player *p, t_map *map, int x, int y)
{
	if (!(map->map[y / 32][(x + 15) / 32] == '1' || \
			map->map[(y + 31) / 32][(x + 15) / 32] == '1' || \
			map->map[y / 32][(x + 16 - 1) / 32] == '1' || \
			map->map[(y + 32 - 1) / 32][(x + 16 - 1) / 32] == '1'))
	{
		p->pos.x = x;
		p->walk++;
	}
}

static void	collide_up(t_player *p, t_map *map, int x, int y)
{
	if (!(map->map[y / 32][x / 32] == '1' || \
			map->map[y / 32][(x + 15) / 32] == '1' || \
			map->map[y / 32][x / 32] == '1' || \
			map->map[y / 32][(x + 16 - 1) / 32] == '1'))
	{
		p->pos.y = y;
		p->walk++;
	}
}

static void	collide_down(t_player *p, t_map *map, int x, int y)
{
	if (!(map->map[(y + 31) / 32][x / 32] == '1' || \
			map->map[(y + 31) / 32][(x + 15) / 32] == '1' || \
			map->map[(y + 32 - 1) / 32][x / 32] == '1' || \
			map->map[(y + 32 - 1) / 32][(x + 16 - 1) / 32] == '1'))
	{
		p->pos.y = y;
		p->walk++;
	}
}

void	wall_collide(t_player *p, t_map *map, double dt)
{
	if (p->anim.sword_anim)
		return ;
	if (p->anim.down)
		collide_down(p, map, p->pos.x, p->pos.y + ((3 * dt) + 2));
	else if (p->anim.up)
		collide_up(p, map, p->pos.x, p->pos.y - ((3 * dt) + 1));
	else if (p->anim.right)
		collide_right(p, map, p->pos.x + ((3 * dt) + 2), p->pos.y);
	else if (p->anim.left)
		collide_left(p, map, p->pos.x - ((3 * dt) + 1), p->pos.y);
}
