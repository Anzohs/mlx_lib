#include "../inc/game.h"

static void	copy_img(t_img *src, t_img *dst, t_vector src_pos, t_vector size)
{
	int	x;
	int	y;
	unsigned int	color;

	y = -1;
	while (++y < size.y)
	{
		x = -1;
		while (++x < size.x)
		{
			color = *(unsigned int *)(src->addr + ((src_pos.y + y) * src->line_len + (src_pos.x + x) * (src->bpp / 8)));
			*(unsigned int *)(dst->addr + (y * dst->line_len + x * (dst->bpp / 8))) = color;
		}
	}
}

void	update_cam(t_game *g)
{
	t_vector	cam_pos;

	cam_pos.x = g->p.pos.x - g->win.size.x / 2;
	cam_pos.y = g->p.pos.y - g->win.size.y / 2;
	if (cam_pos.x + 800 > g->world.pos.x)
		cam_pos.x = g->world.pos.x - 800;
	if (cam_pos.y + 600 > g->world.pos.y)
		cam_pos.y = g->world.pos.y - 600;
	if (cam_pos.x < 0)
		cam_pos.x = 0;
	if (cam_pos.y < 0)
		cam_pos.y = 0;
	copy_img(&g->world, &g->cam, cam_pos, g->win.size);
}
