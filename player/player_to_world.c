/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_to_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:51:18 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/26 18:51:19 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	player_to_world(t_img *w, t_img *p, t_vector pos)
{
	int				y;
	int				x;
	unsigned int	color;

	y = -1;
	while (++y < p->pos.y)
	{
		x = -1;
		while (++x < p->pos.x)
		{
			color = *(unsigned int *)(p->addr + \
				(y * p->line_len + x * (p->bpp / 8)));
			if ((color & 0x00FFFFFF) != 0)
				*(unsigned int *)(w->addr + ((pos.y + y) * \
					w->line_len + (pos.x + x) * (w->bpp / 8))) = color;
		}
	}
}
