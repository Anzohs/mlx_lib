/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_world.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:53:52 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/24 20:54:34 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	write_world(t_game *g, t_map m)
{
	g->i_map.wall.img = mlx_xpm_file_to_image(g->mlx, "tiles.xpm", \
		&g->i_map.wall.pos.x, &g->i_map.wall.pos.y);
	g->i_map.floor.img = mlx_xpm_file_to_image(g->mlx, "groun.xpm", \
		&g->i_map.floor.pos.x, &g->i_map.floor.pos.y);
	g->i_map.floor.addr = mlx_get_data_addr(g->i_map.floor.img, \
		&g->i_map.floor.bpp, &g->i_map.floor.line_len, &g->i_map.floor.endian);
	g->i_map.wall.addr = mlx_get_data_addr(g->i_map.wall.img, \
		&g->i_map.wall.bpp, &g->i_map.wall.line_len, &g->i_map.wall.endian);
}
