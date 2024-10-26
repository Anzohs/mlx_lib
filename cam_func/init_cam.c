/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cam.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 18:06:48 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/26 18:06:49 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	init_cam(t_game *g, t_vector s)
{
	g->cam.img = mlx_new_image(g->mlx, s.x, s.y);
	g->cam.addr = mlx_get_data_addr(g->cam.img, &g->cam.bpp, \
		&g->cam.line_len, &g->cam.endian);
	g->cam.pos = s;
}
