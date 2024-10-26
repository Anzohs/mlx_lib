/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 20:55:37 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/26 20:55:39 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static void	pixel_copy(t_game *g, int src_x, int src_y)
{
	int				x;
	int				y;
	unsigned int	color;

	y = -1;
	while (++y < g->p.sprite.pos.y)
	{
		x = -1;
		while (++x < g->p.sprite.pos.x)
		{
			color = *(unsigned int *)(g->p.sprite.addr + ((src_y + y) * \
				g->p.sprite.line_len + (src_x + x) * (g->p.sprite.bpp / 8)));
			if (color != 0xFF000000)
				*(unsigned int *)(g->p.current.addr + (y * \
					g->p.current.line_len + x * \
					(g->p.current.bpp / 8))) = color;
		}
	}
}

void	draw_p(t_game *g, int src_x, int src_y)
{
	if (g->p.current.img)
		mlx_destroy_image(g->mlx, g->p.current.img);
	g->p.current.img = mlx_new_image(g->mlx, \
		g->p.sprite.pos.x, g->p.sprite.pos.y);
	g->p.current.addr = mlx_get_data_addr(g->p.current.img, &g->p.current.bpp, \
		&g->p.current.line_len, &g->p.current.endian);
	g->p.current.pos = g->p.sprite.pos;
	pixel_copy(g, src_x, src_y);
	player_to_world(&g->world, &g->p.current, g->p.pos);
}
