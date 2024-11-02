/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_g.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 18:32:01 by hladeiro          #+#    #+#             */
/*   Updated: 2024/11/02 18:32:02 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static void	img_destroy(void *mlx, void *img)
{
	if (img && mlx)
		mlx_destroy_image(mlx, img);
}

static void	destroy_collectibles(t_col *c, void *mlx, int n)
{
	int	i;

	i = -1;
	while (++i < n)
		img_destroy(mlx, c->c[i].current.img);
}

static void	free_ttmap(t_map *m)
{
	int	i;

	i = -1;
	while (m->map[++i])
		free(m->map[i]);
	if (m->x_pos)
		free(m->x_pos);
	free(m->map[i]);
	free(m->map);
}

static	void	ft_free_vect(t_game *g)
{
	int	i;

	i = -1;
	if (g->c.c)
	{
		destroy_collectibles(&g->c, g->mlx, g->map->c);
		free(g->c.c);
	}
	if (g->enemy.nb)
	{
		i = -1;
		while (++i < g->enemy.nb)
			img_destroy(g->mlx, g->enemy.enemies[i].current.img);
		free(g->enemy.enemies);
	}
}

void	ft_free_g(t_game *g, int e)
{
	if (e)
		ft_putstr_fd("Fail to allocate memory \n", 2);
	img_destroy(g->mlx, g->e.sprite.img);
	img_destroy(g->mlx, g->p.current.img);
	img_destroy(g->mlx, g->p.atack.img);
	img_destroy(g->mlx, g->p.sprite.img);
	img_destroy(g->mlx, g->cam.img);
	img_destroy(g->mlx, g->c.sprite.img);
	img_destroy(g->mlx, g->enemy.death.img);
	img_destroy(g->mlx, g->enemy.e_img.img);
	img_destroy(g->mlx, g->c.col.img);
	ft_free_vect(g);
	img_destroy(g->mlx, g->i_map.floor.img);
	img_destroy(g->mlx, g->i_map.wall.img);
	img_destroy(g->mlx, g->world.img);
	free(g->map->c_pos);
	free_ttmap(g->map);
	if (g->win.win)
		mlx_destroy_window(g->mlx, g->win.win);
	mlx_destroy_display(g->mlx);
	if (g->mlx)
		free(g->mlx);
	free(g);
	exit(0);
}
