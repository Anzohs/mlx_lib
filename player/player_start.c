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

void	player_start(t_game *g)
{
	g->p.ar = (t_area){g->p.pos, (t_vector){16, 32}};
	g->p.score = 0;
	g->p.health = 0;
	g->p.health = 3;
	g->p.sprite = (t_img){0};
	g->p.sprite.img = mlx_xpm_file_to_image(g->mlx, "character_walk.xpm", \
		&g->p.sprite.pos.x, &g->p.sprite.pos.y);
	g->p.sprite.addr = mlx_get_data_addr(g->p.sprite.img, \
		&g->p.sprite.bpp, &g->p.sprite.line_len, &g->p.sprite.endian);
	g->p.sprite.pos = (t_vector){16, 32};
	g->p.anim = (t_sprite){0};
	g->p.anim.nb_frame = 4;
	g->p.current = (t_img){0};
}
