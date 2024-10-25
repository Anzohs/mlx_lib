#include "../inc/game.h"

void	init_cam(t_game *g, t_vector s)
{
	g->cam.img = mlx_new_image(g->mlx, s.x, s.y);
	g->cam.addr = mlx_get_data_addr(g->cam.img, &g->cam.bpp, \
		&g->cam.line_len, &g->cam.endian);
	g->cam.pos = s;
}
