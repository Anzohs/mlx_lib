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

static void	render_game(t_game *g)
{
	render_map(g, g->map);
	draw_exit(g);
	if (g->map->x)
		draw_enemy(g);
	render_coll(g);
	if (g->p.anim.sword_anim)
		draw_p(g, g->p.anim.frame * g->p.atack.pos.x, \
			g->p.anim.row * g->p.atack.pos.y);
	else
		draw_p(g, g->p.anim.frame * g->p.sprite.pos.x, \
			g->p.anim.row * g->p.sprite.pos.y);
	update_cam(g);
	game_to_win(g);
}

int	update_game(t_game *g, double dt)
{
	key_released(&g->p, g->keydown);
	key_pressed(&g->p, g->keydown);
	player_update(g, &g->p, dt);
	update_enemy(g);
	update_col(g, dt);
	render_game(g);
	update_exit(g);
	ft_putstr_fd("Player walk :", 1);
	ft_putnbr_fd(g->p.walk, 1);
	ft_putchar_fd('\n', 1);
	mlx_put_str(g);
	return (1);
}
