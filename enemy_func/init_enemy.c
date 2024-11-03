/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 19:14:28 by hladeiro          #+#    #+#             */
/*   Updated: 2024/11/02 19:14:29 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static void	enemy_start(t_game *g)
{
	int	i;

	i = -1;
	while (++i < g->enemy.nb)
	{
		g->enemy.enemies[i] = (t_enemy){0};
		g->enemy.enemies[i].pos.x = g->map->x_pos[i].x * 32;
		g->enemy.enemies[i].pos.y = g->map->x_pos[i].y * 32;
		g->enemy.enemies[i].is_alive = true;
	}
}

static void	enemy_img(t_enm *e, t_game *g)
{
	e->e_img.img = mlx_xpm_file_to_image(g->mlx, "assets/enemy.xpm", \
		&e->e_img.pos.x, &e->e_img.pos.y);
	e->death.img = mlx_xpm_file_to_image(g->mlx, "assets/cross.xpm", \
		&e->death.pos.x, &e->death.pos.y);
	if (!e->e_img.img || !e->death.img)
		ft_free_g(g, 1);
	e->e_img.addr = mlx_get_data_addr(e->e_img.img, &e->e_img.bpp, \
		&e->e_img.line_len, &e->e_img.endian);
	e->death.addr = mlx_get_data_addr(e->death.img, &e->death.bpp, \
		&e->death.line_len, &e->death.endian);
	e->e_img.pos = (t_vector){24, 24};
	e->death.pos = (t_vector){20, 32};
}

void	init_enemy(t_game *g, int n)
{
	if (!n)
		return ;
	g->enemy.enemies = ft_calloc(n + 1, sizeof(t_enemy));
	if (!g->enemy.enemies)
		ft_free_g(g, 1);
	g->enemy.nb = n;
	enemy_start(g);
	enemy_img(&g->enemy, g);
}
