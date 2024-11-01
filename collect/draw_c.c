/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:44:28 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/28 17:44:29 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static t_img	*get(bool collected, t_game *g)
{
	if (collected)
		return (&g->c.col);
	return (&g->c.sprite);
}

static void	pixel_c(t_game *g, int src_x, int src_y, int n, bool collected)
{
	int				x;
	int				y;
	unsigned int	color;
	t_img			*img;

	img = get(collected, g);
	y = -1;
	while (++y < img->pos.y)
	{
		x = -1;
		while (++x < img->pos.x)
		{
			color = *(unsigned int *)(img->addr + ((src_y + y) * \
				img->line_len + (src_x + x) * (img->bpp / 8)));
			if (color != 0xFF000000)
				*(unsigned int *)(g->c.c[n].current.addr + (y * \
					g->c.c[n].current.line_len + x * \
					(g->c.c[n].current.bpp / 8))) = color;
		}
	}
}

void	draw_c(t_game *g, int src_x, int src_y, int n)
{
	if (g->c.c[n].current.img)
		mlx_destroy_image(g->mlx, g->c.c[n].current.img);
	g->c.c[n].current.img = mlx_new_image(g->mlx, \
		g->c.sprite.pos.x, g->c.sprite.pos.y);
	if (!g->c.c[n].current.img)
		ft_free_g(g, 1);
	g->c.c[n].current.addr = mlx_get_data_addr(g->c.c[n].current.img, \
		&g->c.c[n].current.bpp, &g->c.c[n].current.line_len, \
			&g->c.c[n].current.endian);
	g->c.c[n].current.pos = g->c.sprite.pos;
	pixel_c(g, src_x, src_y, n, g->c.c[n].collected);
    collectable_to_w(&g->world, &g->c.c[n].current, g->c.c[n].pos);
}
