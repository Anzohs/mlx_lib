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
	const double	fps = 1.0 / 30.0;

	c->acc_time += dt;
	while (c->acc_time >= fps)
	{
		c->frame = anim_index(&c->anim_acc_time, \
			c->nb_frame, c->frame, fps);
		c->acc_time -= fps;
	}
}
