/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_col.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:55:07 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/28 17:55:08 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	update_col(t_game *g, double dt)
{
	int	i;

	i = -1;
	while (++i < g->map->c)
	{
		collectable_update(&g->c.c[i], dt);
		if (!g->c.c[i].collected && is_colliding(g->c.c[i], g->p))
		{
			g->c.c[i].collected = true;
			g->c.c[i].nb_frame -= 1;
			g->c.c[i].frame = g->c.c[i].nb_frame - 1;
			g->p.score++;
		}
	}
}
