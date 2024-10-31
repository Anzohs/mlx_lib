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

static void	game_to_win(t_game *g)
{
	mlx_put_image_to_window(g->mlx, g->win.win, g->cam.img, 0, 0);
}

static void	render_game(t_game *g)
{
	render_map(g, g->map);
	draw_exit(g);
	render_coll(g);
	if (g->p.anim.sword_anim)
		draw_p(g, g->p.anim.frame * g->p.atack.pos.x, g->p.anim.row * g->p.atack.pos.y);
	else
		draw_p(g, g->p.anim.frame * g->p.sprite.pos.x, g->p.anim.row * g->p.sprite.pos.y);
	update_cam(g);
	game_to_win(g);
}

static void	key_press(t_game *g,bool key[280])
{
	if ((key[32] || key[49]) && !g->p.anim.sword_anim)
	{
		g->p.anim.sword_anim = true;
		g->p.anim.animating = false;
        g->p.anim.frame = 0;
	}
	else if (key[13] || key[119])
	{
		g->p.anim.up = 1;
		g->p.anim.row = 2;
		g->p.anim.animating = true;
	}
	else if (key[115] || key[1])
	{
		g->p.anim.down = 1;
		g->p.anim.row = 0;
		g->p.anim.animating = true;
	}
	else if ((key[97] || key[0]))
	{
		g->p.anim.left = 1;
		g->p.anim.row = 3;
		g->p.anim.animating = true;
	}
	else if (key[100] || key[2])
	{
		g->p.anim.right = 1;
		g->p.anim.row = 1;
		g->p.anim.animating = true;
	}
	if (!g->p.anim.down && !g->p.anim.up && !g->p.anim.left && !g->p.anim.right && !g->p.anim.sword_anim)
	{
		g->p.anim.animating = false;
		g->p.anim.frame = 0;
	}
}

static void key_release(t_game *g, bool key[280])
{
	if (!key[13] || !key[119])
		g->p.anim.up = 0;
	if (!key[115] || !key[1])
		g->p.anim.down = 0;
	if (!key[97] || !key[0])
		g->p.anim.left = 0;
	if (!key[100] || !key[2])
		g->p.anim.right = 0;
	if ((!key[32] || !key[49]) && g->p.anim.sword_anim)
		g->p.anim.animating = true;
}

int	update_game(t_game *g, double dt)
{
	key_release(g, g->keydown);
	key_press(g, g->keydown);
	player_update(g, &g->p, dt);
	update_col(g, dt);
	render_game(g);
	update_exit(g);
	ft_putstr_fd("Player walk :", 1);
	ft_putnbr_fd(g->p.walk, 1);
	ft_putchar_fd('\n', 1);
	return (1);
}
