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

static void	pixel_copy_sw(t_game *g, int src_x, int src_y)
{
	int				x;
	int				y;
	unsigned int	color;

	y = -1;
	while (++y < g->p.atack.pos.y)
	{
		x = -1;
		while (++x < g->p.atack.pos.x)
		{
			color = *(unsigned int *)(g->p.atack.addr + ((src_y + y) * \
				g->p.atack.line_len + (src_x + x) * (g->p.atack.bpp / 8)));
			if (color != 0xFF000000)
				*(unsigned int *)(g->p.current.addr + (y * \
					g->p.current.line_len + x * \
					(g->p.current.bpp / 8))) = color;
		}
	}
}

static void	player_attack(t_img *w, t_img *p, t_vector pos)
{
	int				y;
	int				x;
	unsigned int	color;
	t_vector		v;

	v = pos;
	v.x = v.x -5;
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

static void	get_img(t_player *p, t_game *g)
{
	if (p->anim.sword_anim)
		p->current.img = mlx_new_image(g->mlx, p->atack.pos.x, p->atack.pos.y);
	else
		p->current.img = mlx_new_image(g->mlx, p->sprite.pos.x, \
			p->sprite.pos.y);
	if (!p->current.img)
		ft_free_g(g, 1);
}

void	draw_p(t_game *g, int src_x, int src_y)
{
	t_vector	adju;

	get_img(&g->p, g);
	g->p.current.addr = mlx_get_data_addr(g->p.current.img, &g->p.current.bpp, \
		&g->p.current.line_len, &g->p.current.endian);
	if (g->p.anim.sword_anim)
	{
		adju = g->p.pos;
		adju.x -= (g->p.atack.pos.x - g->p.sprite.pos.x) / 2;
		adju.y -= (g->p.atack.pos.y - g->p.sprite.pos.y) / 2;
		g->p.current.pos = g->p.atack.pos;
		if (g->p.anim.row == 1)
			pixel_copy_sw(g, src_x, g->p.atack.pos.y * 2);
		else if (g->p.anim.row == 2)
			pixel_copy_sw(g, src_x, g->p.atack.pos.y * 1);
		else
			pixel_copy_sw(g, src_x, src_y);
		player_attack(&g->world, &g->p.current, adju);
	}
	else
	{
		g->p.current.pos = g->p.sprite.pos;
		pixel_copy(g, src_x, src_y);
		player_to_world(&g->world, &g->p.current, g->p.pos);
	}
}
