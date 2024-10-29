/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 22:19:42 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/26 22:19:43 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static void	game_to_win(t_game *g)
{
	mlx_put_image_to_window(g->mlx, g->win.win, g->cam.img, 0, 0);
}

static void	pixel_e(t_game *g, int src_x, int src_y)
{
	int				x;
	int				y;
	unsigned int	color;
	t_img			*img;

	y = -1;
	while (++y < img->pos.y)
	{
		x = -1;
		while (++x < img->pos.x)
		{
			color = *(unsigned int *)(img->addr + ((src_y + y) * \
				img->line_len + (src_x + x) * (img->bpp / 8)));
			if (color != 0xFF000000)
				*(unsigned int *)(g->e.sprite.addr + (y * \
					g->e.sprite.line_len + x * \
					(g->c.sprite.bpp / 8))) = color;
		}
	}
}

static void	exit_to_w(t_img *w, t_img *e, t_vector pos)
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

static	void	draw_e(t_game *g)
{
	pixel_e(g, 0, 0);
	exit_to_w(g->world.img, &g->e.sprite, g->e.sprite.pos);
}

static void	render_game(t_game *g)
{
	render_map(g, g->map);
	render_coll(g);
	draw_p(g, g->p.anim.frame * g->p.sprite.pos.x, g->p.anim.row * g->p.sprite.pos.y);
	draw_e(g);
	update_cam(g);
	game_to_win(g);
}

int	update_game(t_game *g, double dt)
{
	player_update(g, &g->p, dt);
	update_col(g, dt);
	render_game(g);
	return (1);
}
