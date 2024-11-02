/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:06:21 by hladeiro          #+#    #+#             */
/*   Updated: 2024/11/02 19:06:22 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static void	exit_to_world(t_img *w, t_img *e, t_vector pos)
{
	int				y;
	int				x;
	unsigned int	color;

	y = -1;
	while (++y < e->pos.y)
	{
		x = -1;
		while (++x < e->pos.x)
		{
			color = *(unsigned int *)(e->addr + \
				(y * e->line_len + x * (e->bpp / 8)));
			if ((color & 0x00FFFFFF) != 0)
				*(unsigned int *)(w->addr + ((pos.y + y) * \
					w->line_len + (pos.x + x) * (w->bpp / 8))) = color;
		}
	}
}

void	draw_exit(t_game *g)
{
	exit_to_world(&g->world, &g->e.sprite, g->e.pos);
}
