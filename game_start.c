/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 21:35:06 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/23 21:35:08 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/game.h"
#include "mlx/mlx.h"

#define KEY_W 13
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_UP 119
#define KEY_DOWN 115
#define KEY_LEFT 97
#define KEY_RIGHT 100
#define KEY_ESC 53

static void	free_tmap(t_map *m)
{
	int	i;

	i = -1;
	while (++i < m->size.y)
		free(m->map[i]);
	free(m->map[i]);
	free(m);
}
/*
static void	draw_p(t_game *g)
{
	int	src_x = g->p.anim.frame * g->p.sprite.pos.x;
	int	src_y = g->p.anim.row * g->p.sprite.pos.y;
	int	x;
	int	y;
	unsigned int color;

	if (g->p.current.img)
		mlx_destroy_image(g->mlx, g->p.current.img);
	g->p.current.img = mlx_new_image(g->mlx, g->p.sprite.pos.x, g->p.sprite.pos.y);
	g->p.current.addr = mlx_get_data_addr(g->p.current.img, &g->p.current.bpp,
		&g->p.current.line_len, &g->p.current.endian);
	g->p.current.pos = g->p.sprite.pos;
	y = -1;
	while (++y < g->p.sprite.pos.y)
	{
		x = -1;
		while (++x < g->p.sprite.pos.x)
		{
			color = *(unsigned int *)(g->p.sprite.addr + ((src_y + y) * g->p.sprite.line_len + (src_x + x) * (g->p.sprite.bpp / 8)));
			if (color != 0xFF000000)
				*(unsigned int *)(g->p.current.addr + (y * g->p.current.line_len + x * (g->p.current.bpp / 8))) = color;
		}
	}
	player_to_world(&g->world, &g->p.current, g->p.pos);
}*/

static int an(t_game *g, double delta_time)
{
	static double	accumulated_time;
	static double 	animation_acc;
	const double	frame_time = 1.0 / 30.0;
	const double	animation_time = 1.0 / 4.0;

    accumulated_time += delta_time;
    while (accumulated_time >= frame_time)
    {
        if (g->p.anim.animating)
        {
            animation_acc += frame_time;
            if (animation_acc >= animation_time)
            {
                g->p.anim.frame = (g->p.anim.frame + 1) % g->p.anim.nb_frame;
                animation_acc -= animation_time;
            }
        }
        wall_collide(&g->p, g->map, delta_time);
        g->p.anim.animating = (g->p.anim.down || g->p.anim.up || g->p.anim.right || g->p.anim.left);
        accumulated_time -= frame_time;
    }
    render_map(g, g->map);
    draw_p(g, g->p.anim.frame * g->p.sprite.pos.x, g->p.anim.row * g->p.sprite.pos.y);
    update_cam(g);
    mlx_put_image_to_window(g->mlx, g->win.win, g->cam.img, 0, 0);
    return 1;
}

static int	animate(t_game *g)
{
	an(g, g->dt());
	return (0);
}

void	game_start(t_map map)
{
	t_game	*g;

	g = init_game("so_long", (t_vector){800, 600});
	g->p.pos.x = map.p_pos.x * 32;
	g->p.pos.y = map.p_pos.y * 32;
	g->e.pos = map.e_pos;
	g->map = &map;
	g->animate = animate;
	init_world(g, map.size);
	init_cam(g, (t_vector){800, 600});
	write_world(g, map);
	player_start(g);
	render_map(g, g->map);
	draw_p(g, g->p.anim.frame * g->p.sprite.pos.x, g->p.anim.row * g->p.sprite.pos.y);
	update_cam(g);
	event_handler(g);
	g->loop(g);
}
