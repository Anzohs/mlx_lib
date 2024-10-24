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

#include "inc/game.h"

void	loop(t_game	*g)
{
	mlx_loop(g->mlx);
}

int	exit_t(t_game *g)
{
	if (g)
	{
		if (g->win.win)
			mlx_destroy_window(g->mlx, g->win.win);
		if (g->world.img)
			mlx_destroy_image(g->mlx, g->world.img);
		if (g->mlx)
		{
			mlx_destroy_display(g->mlx);
			free(g->mlx);
		}
		free(g);
	}
	exit(0);
	return (0);
}

t_game	*init_game(char *name, t_vector s)
{
	t_game	*game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		return (NULL);
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_t(game);
	game->win.mlx = game->mlx;
	game->win.win = mlx_new_window(game->mlx, s.x, s.y, name);
	if (!game->win.win)
		exit_t(game);
	mlx_hook(game->win.win, 17, (1L << 0), &exit_t, game);
	game->win.size = s;
	return (game);
}
