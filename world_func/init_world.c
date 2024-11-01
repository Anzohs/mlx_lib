/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_world.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:31:12 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/24 20:31:13 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	init_world(t_game *g, t_vector size)
{
	g->world.pos.x = size.x * 32;
	g->world.pos.y = size.y * 32;
	if (g->world.pos.x < 800)
		g->world.pos.x = 800;
	if (g->world.pos.y < 600)
		g->world.pos.y = 600;
	g->world.img = mlx_new_image(g->mlx, g->world.pos.x, g->world.pos.y);
	if (!g->world.img)
		ft_free_g(g, 1);
	g->world.addr = mlx_get_data_addr(g->world.img, &g->world.bpp, \
		&g->world.line_len, &g->world.endian);
}
