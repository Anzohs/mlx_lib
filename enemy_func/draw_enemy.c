/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:14:56 by hladeiro          #+#    #+#             */
/*   Updated: 2024/11/02 19:14:57 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static void	enemy_to_w(t_img *w, t_img *c, t_vector pos)
{
	int				y;
	int				x;
	unsigned int	color;

	y = -1;
	while (++y < c->pos.y)
	{
		x = -1;
		while (++x < c->pos.x)
		{
			color = *(unsigned int *)(c->addr + \
				(y * c->line_len + x * (c->bpp / 8)));
			if ((color & 0x00FFFFFF) != 0)
				*(unsigned int *)(w->addr + ((pos.y + y) * \
					w->line_len + (pos.x + x) * (w->bpp / 8))) = color;
		}
	}
}

static void	pixel_cpy(t_enemy *e, t_img *img)
{
	int				x;
	int				y;
	unsigned int	color;

	y = -1;
	while (++y < img->pos.y)
	{
		x = -1;
		while (++x < img->pos.x)
		{
			color = *(unsigned int *)(img->addr + ((0 + y) * \
				img->line_len + (0 + x) * (img->bpp / 8)));
			if (color != 0xFF000000)
				*(unsigned int *)(e->current.addr + (y * \
					e->current.line_len + x * \
					(e->current.bpp / 8))) = color;
		}
	}
}

static void	enemy_img(t_enemy *e, t_game *g, t_enm *en)
{
	if (e->current.img)
		mlx_destroy_image(g->mlx, e->current.img);
	if (e->is_alive)
	{
		e->current.img = mlx_new_image(g->mlx, en->e_img.pos.x, \
			en->e_img.pos.y);
		e->current.pos = en->e_img.pos;
	}
	else
	{
		e->current.img = mlx_new_image(g->mlx, en->death.pos.x, \
			en->death.pos.y);
		e->current.pos = en->death.pos;
	}
	e->current.addr = mlx_get_data_addr(e->current.img, &e->current.bpp, \
		&e->current.line_len, &e->current.endian);
	if (e->is_alive)
		pixel_cpy(e, &en->e_img);
	else
		pixel_cpy(e, &en->death);
	enemy_to_w(&g->world, &e->current, e->pos);
}

void	draw_enemy(t_game *g)
{
	int	i;

	i = -1;
	while (++i < g->enemy.nb)
		enemy_img(&g->enemy.enemies[i], g, &g->enemy);
}
