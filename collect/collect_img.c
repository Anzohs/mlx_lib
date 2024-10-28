/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:54:39 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/28 18:56:53 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	collect_img(t_game *g, t_col *c)
{
	c->sprite.img = mlx_xpm_file_to_image(g->mlx, "cristal.xpm", \
		&c->sprite.pos.x, &c->sprite.pos.y);
	c->sprite.addr = mlx_get_data_addr(c->sprite.img, &c->sprite.bpp, \
		&c->sprite.line_len, &c->sprite.endian);
	c->sprite.pos = (t_vector){16, 16};
}
