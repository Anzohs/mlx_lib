/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collected_img.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:57:02 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/28 18:57:03 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	collected_img(t_game *g, t_col *c)
{
	c->col.img = mlx_xpm_file_to_image(g->mlx, "crystal_collected.xpm", \
		&c->col.pos.x, &c->col.pos.y);
	if (!c->col.img)
		ft_free_g(g, 1);
	c->col.addr = mlx_get_data_addr(c->col.img, &c->col.bpp, \
		&c->col.line_len, &c->col.endian);
	c->col.pos = (t_vector){16, 16};
}
