/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:27:42 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/24 22:27:44 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static void	draw_tile(t_game *g, t_img *img, int x, int y)
{
	int				j;
	int				i;
	unsigned int	color;

	i = -1;
	while (++i < 32)
	{
		j = -1;
		while (++j < 32)
		{
			color = *(unsigned int *)(img->addr + ((i % 16) * img->line_len + \
				(j % 16) * (img->bpp / 8)));
			*(unsigned int *)(g->world.addr + ((y + i) * g->world.line_len + \
				(x + j) * (g->world.bpp / 8))) = color;
		}
	}
}

void	render_map(t_game *g, t_map *m)
{
	int	y;
	int	x;

	y = -1;
	while (++y < m->size.y)
	{
		x = -1;
		while (++x < m->size.x)
		{
			if (m->map[y][x] == '1')
				draw_tile(g, &g->i_map.wall, x * 32, y * 32);
			else
				draw_tile(g, &g->i_map.floor, x * 32, y * 32);
		}
	}
}
