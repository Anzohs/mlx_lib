/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_coll.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:59:57 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/28 17:59:58 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	render_coll(t_game *g)
{
	int	i;

	i = -1;
	while (++i < g->map->c)
	{
		if (g->c.c[i].collected)
			draw_c(g, g->c.c[i].frame * g->c.col.pos.x, 0, i);
		else
			draw_c(g, g->c.c[i].frame * g->c.sprite.pos.x, 0, i);
	}
}
