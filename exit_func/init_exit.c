/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:06:30 by hladeiro          #+#    #+#             */
/*   Updated: 2024/11/02 19:06:32 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	init_exit(t_game *g)
{
	g->e.sprite = (t_img){0};
	g->e.sprite.img = mlx_xpm_file_to_image(g->mlx, "assets/exit.xpm", \
		&g->e.sprite.pos.x, &g->e.sprite.pos.y);
	if (!g->e.sprite.img)
		ft_free_g(g, 1);
	g->e.sprite.addr = mlx_get_data_addr(g->e.sprite.img, &g->e.sprite.bpp, \
		&g->e.sprite.line_len, &g->e.sprite.endian);
	g->e.pos.x *= 32;
	g->e.pos.y *= 32;
	g->e.sprite.pos = (t_vector){32, 32};
	g->e.is_open = false;
}
