/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 01:11:30 by hladeiro          #+#    #+#             */
/*   Updated: 2024/11/03 01:11:31 by hladeiro         ###   ########.fr       */
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

void	animation_up(t_enemy *e, double dt)
{
	const double	fps = 1.0 / 30.0;

	e->acc_time += dt;
	while (e->acc_time >= fps)
	{
		e->frame = anim_index(&e->anim_acc_time, 4, e->frame, fps);
		e->acc_time -= fps;
	}
}
