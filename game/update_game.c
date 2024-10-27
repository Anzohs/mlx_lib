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
#include <stdbool.h>

static void	pixel_c(t_game *g, int src_x, int src_y, int n, bool collected)
{
	int				x;
	int				y;
	unsigned int	color;
	t_img			*img;

	img = collected ? &g->c.col : &g->c.sprite;

	y = -1;
	while (++y < img->pos.y)
	{
		x = -1;
		while (++x < img->pos.x)
		{
			color = *(unsigned int *)(img->addr + ((src_y + y) * \
				img->line_len + (src_x + x) * (img->bpp / 8)));
			if (color != 0xFF000000) // Ensure transparency check is correct
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
    g->c.c[n].current.addr = mlx_get_data_addr(g->c.c[n].current.img, &g->c.c[n].current.bpp, \
        &g->c.c[n].current.line_len, &g->c.c[n].current.endian);
    g->c.c[n].current.pos = g->c.sprite.pos;
    pixel_c(g, src_x, src_y, n, g->c.c[n].collected);
    collectable_to_w(&g->world, &g->c.c[n].current, g->c.c[n].pos);
}

static void	game_to_win(t_game *g)
{
	mlx_put_image_to_window(g->mlx, g->win.win, g->cam.img, 0, 0);
}

static void coll(t_game *g)
{
	int i = -1;
	while (++i < g->map->c)
	{
		if (g->c.c[i].collected)
			draw_c(g, g->c.c[i].frame * g->c.col.pos.x, 0, i); // Use collected sprite
		else
			draw_c(g, g->c.c[i].frame * g->c.sprite.pos.x, 0, i); // Use normal sprite
	}
}

static void	render_game(t_game *g)
{
	render_map(g, g->map);
	coll(g);
	draw_p(g, g->p.anim.frame * g->p.sprite.pos.x, g->p.anim.row * g->p.sprite.pos.y);
	update_cam(g);
	game_to_win(g);
}

static void coll_up(t_game *g, double dt)
{
	int i = -1;
	while (++i < g->map->c)
	{
		collectable_update(&g->c.c[i], dt);
		if (!g->c.c[i].collected && is_colliding(g->c.c[i], g->p))
		{
			g->c.c[i].collected = true;
			// Add any additional logic for when a collectable is collected
		}
	}
}

int	update_game(t_game *g, double dt)
{
	player_update(g, &g->p, dt);
	coll_up(g, dt);
	render_game(g);
	return (1);
}
