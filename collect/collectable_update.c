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

void	collectable_update(t_colectable *c, double dt)
{
	static double	acc_time;
	static double	anim_acc_time;
	const double	fps = 1.0 / 30.0;

	acc_time += dt;
	while (acc_time >= fps)
	{
		c->frame = anim_index(&anim_acc_time, \
			c->nb_frame, c->frame, fps);
		acc_time -= fps;
	}
}
