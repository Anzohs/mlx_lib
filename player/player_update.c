/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 13:59:44 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/27 13:59:45 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/game.h"

static int	anim_index(double *time, int nb_frames, int frame, double fps)
{
	const double	anim_time = 1.0 / 4.0;

	*time += fps;
	if (*time >= anim_time)
	{
		frame = (frame + 1) % nb_frames;
		*time -= anim_time;
	}
	return (frame);
}

void	player_update(t_game *g, t_player *p, double dt)
{
	static double	acc_time;
	static double	anim_acc_time;
	const double	fps = 1.0 / 30.0;

	acc_time += dt;
	while (acc_time >= fps)
	{
		if (p->anim.sword_anim)
		{
			p->anim.frame = anim_index(&anim_acc_time, \
				p->anim.nb_frame, p->anim.frame, fps);
			if (p->anim.frame == p->anim.nb_frame - 1)
			{
				p->anim.sword_anim = false;
				p->anim.frame = 0;
				p->anim.animating = false;
				return ;
			}
		}
		else if (p->anim.animating)
			p->anim.frame = anim_index(&anim_acc_time, \
				p->anim.nb_frame, p->anim.frame, fps);
		wall_collide(p, g->map, dt);
		acc_time -= fps;
	}
}
