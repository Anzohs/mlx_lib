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
#include "inc/structs.h"
#include "time.h"

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
			//mlx_destroy_display(g->mlx);
			free(g->mlx);
		}
		free(g);
	}
	exit(0);
	return (0);
}

static int	limit_fps(unsigned int frame_rendering_time, unsigned int fps_max)
{
	if (!fps_max)
		fps_max = 60;
	if (frame_rendering_time < (CLOCKS_PER_SEC / fps_max))
	{
		usleep((CLOCKS_PER_SEC / fps_max) - frame_rendering_time);
		frame_rendering_time = (CLOCKS_PER_SEC / fps_max);
	}
	return (CLOCKS_PER_SEC / frame_rendering_time);
}

static int	update(t_game *g)
{
	//clock_t	update_time;


	if(g->animate)
		g->animate(g);
	//update_time = clock();
	//g->frame_rendering_time = clock() - update_time;
	//g->fps = limit_fps(g->frame_rendering_time, 60);
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
	game->loop = loop;
	game->p = (t_player){0};
	game->dt = 0;
	mlx_loop_hook(game->mlx, &update, game);
	return (game);
}
