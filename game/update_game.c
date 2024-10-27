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
	draw_p(g, g->p.anim.frame * g->p.sprite.pos.x, g->p.anim.row * g->p.sprite.pos.y);
	update_cam(g);
	game_to_win(g);
}

int	update_game(t_game *g, double dt)
{
	player_update(g, &g->p, dt);
	render_game(g);
	return (1);
}
