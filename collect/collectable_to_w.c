#include "../inc/game.h"

void	collectable_to_w(t_img *w, t_img *c, t_vector pos)
{
	int				y;
	int				x;
	unsigned int	color;

	y = -1;
	while (++y < c->pos.y)
	{
		x = -1;
		while (++x < c->pos.x)
		{
			color = *(unsigned int *)(c->addr + \
				(y * c->line_len + x * (c->bpp / 8)));
			if ((color & 0x00FFFFFF) != 0)
				*(unsigned int *)(w->addr + ((pos.y + y) * \
					w->line_len + (pos.x + x) * (w->bpp / 8))) = color;
		}
	}
}
