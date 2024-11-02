/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_start.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:35:08 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/26 19:35:09 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static void	get_img(t_player *p, t_game *g)
{
	p->sprite.img = mlx_xpm_file_to_image(g->mlx, "assets/character_walk.xpm", \
		&p->sprite.pos.x, &p->sprite.pos.y);
	p->atack.img = mlx_xpm_file_to_image(g->mlx, "assets/character_sword.xpm", \
		&p->atack.pos.x, &p->atack.pos.y);
	if (!p->sprite.img || !p->atack.img)
		ft_free_g(g, 1);
}

void	player_start(t_game *g)
{
	g->p.ar = (t_area){g->p.pos, (t_vector){16, 32}};
	g->p.score = 0;
	g->p.side = 0;
	g->p.sprite = (t_img){0};
	get_img(&g->p, g);
	g->p.sprite.addr = mlx_get_data_addr(g->p.sprite.img, \
		&g->p.sprite.bpp, &g->p.sprite.line_len, &g->p.sprite.endian);
	g->p.atack.addr = mlx_get_data_addr(g->p.atack.img, \
		&g->p.atack.bpp, &g->p.atack.line_len, &g->p.atack.endian);
	g->p.sprite.pos = (t_vector){16, 32};
	g->p.atack.pos = (t_vector){32, 32};
	g->p.anim = (t_sprite){0};
	g->p.anim.nb_frame = 4;
	g->p.current = (t_img){0};
	g->p.walk = 0;
	g->p.anim.sword_anim = false;
}
