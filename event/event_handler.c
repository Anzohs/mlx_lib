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
#include <stdbool.h>

static void	set_anim(t_game *g, int r)
{
	g->p.anim.row = r;
	g->p.anim.animating = true;
}

static void	reset_flags(t_player *p)
{
	p->anim.up = 0;
	p->anim.down = 0;
	p->anim.left = 0;
	p->anim.right = 0;
}

static int	keypress(int key, t_game *g)
{
	if (key == 53)
		exit(0);
	if ((key == 119 || key == 13) && !g->p.anim.sword_anim)
	{
		g->p.anim.up = 1;
		set_anim(g, 2);
	}
	else if ((key == 115 || key == 1) && !g->p.anim.sword_anim)
	{
		g->p.anim.down = 1;
		set_anim(g, 0);
	}
	else if ((key == 97 || key == 0) && !g->p.anim.sword_anim)
	{
		g->p.anim.left = 1;
		set_anim(g, 3);
	}
	else if ((key == 100 || key == 2) && !g->p.anim.sword_anim)
	{
		g->p.anim.right = 1;
		set_anim(g, 1);
	}
	else if (key == 32)
	{
		g->p.anim.sword_anim = true;
		g->p.anim.animating = false;
		g->p.anim.frame = 0;
	}
	return (0);
}

static int	keyrelease(int k, t_game *g)
{
	if (g->p.anim.sword_anim)
		return (0);
	if (k == 119 || k == 13)
		g->p.anim.up = 0;
	else if (k == 115 || k == 1)
		g->p.anim.down = 0;
	else if (k == 97 || k == 0)
		g->p.anim.left = 0;
	else if (k == 100 || k == 2)
		g->p.anim.right = 0;
	if (!g->p.anim.down && !g->p.anim.up && !g->p.anim.left && !g->p.anim.right)
	{
		g->p.anim.animating = false;
		g->p.anim.frame = 0;
	}
	return (0);
}

void	event_handler(t_game *game)
{
	mlx_hook(game->win.win, 2, 1L << 0, keypress, game);
	mlx_hook(game->win.win, 3, 1L << 1, keyrelease, game);
	mlx_do_key_autorepeatoff(game->mlx);
}
