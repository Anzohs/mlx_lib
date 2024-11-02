/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 18:58:34 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/21 18:58:35 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

void	ft_free_map(t_map *m)
{
	int	i;

	i = -1;
	while (i++ < m->size.y)
		free(m->map[i]);
	free(m->map[i]);
	if (m->c_pos)
		free(m->c_pos);
	if (m->x_pos)
		free(m->x_pos);
	free(m);
	exit(0);
}

void	loop(t_game	*g)
{
	mlx_loop(g->mlx);
}

int	exit_t(t_game *g)
{
	ft_free_g(g, 0);
	return (1);
}

static int	update(t_game *g)
{
	if (g->animate)
		g->animate(g);
	return (0);
}

t_game	*init_game(char *name, t_vector s, t_map *m)
{
	t_game	*game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		ft_free_map(m);
	game->map = m;
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_free_g(game, 1);
	game->win.mlx = game->mlx;
	game->win.win = mlx_new_window(game->mlx, s.x, s.y, name);
	if (!game->win.win)
		ft_free_g(game, 1);
	mlx_hook(game->win.win, 17, (1L << 0), &exit_t, game);
	game->win.size = s;
	game->loop = loop;
	game->p = (t_player){0};
	game->dt = get_delta;
	mlx_loop_hook(game->mlx, &update, game);
	return (game);
}
