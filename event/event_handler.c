/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:17:52 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/26 19:17:53 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static int	keypress(int key, t_game *g)
{
	if (key == 53 || key == 65307)
		ft_free_g(g, 0);
	if (key < 280)
		g->keydown[key] = true;
	return (0);
}

static int	keyrelease(int k, t_game *g)
{
	g->keydown[k] = false;
	return (0);
}

void	event_handler(t_game *game)
{
	mlx_hook(game->win.win, 2, 1L << 0, keypress, game);
	mlx_hook(game->win.win, 3, 1L << 1, keyrelease, game);
	mlx_do_key_autorepeatoff(game->mlx);
}
