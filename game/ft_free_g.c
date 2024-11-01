# include "../inc/game.h"

static void	img_destroy(void *mlx, void *img)
{
	if (img && mlx)
		mlx_destroy_image(mlx, img);
}

static void	destroy_collectibles(t_col *c, void *mlx, int n)
{
	int i;

	i = -1;
	while (++i < n)
		img_destroy(mlx, c->c[i].current.img);
}

static void	free_ttmap(t_map *m)
{
	int	i;

	i = -1;
	while (m->map[++i])
		free(m->map[i]);
	free(m->map[i]);
	free(m->map);
}

void	ft_free_g(t_game *g, int e)
{
	if (e)
		ft_putstr_fd("Fail to allocate memory \n", 2);
	if (g->c.c)
	{
		destroy_collectibles(&g->c, g->mlx, g->map->c);
		free(g->c.c);
	}
	img_destroy(g->mlx, g->e.sprite.img);
	img_destroy(g->mlx, g->p.current.img);
	img_destroy(g->mlx, g->p.atack.img);
	img_destroy(g->mlx, g->p.sprite.img);
	img_destroy(g->mlx, g->cam.img);
	img_destroy(g->mlx, g->c.sprite.img);
	img_destroy(g->mlx, g->c.col.img);
	img_destroy(g->mlx, g->i_map.floor.img);
	img_destroy(g->mlx, g->i_map.wall.img);
	img_destroy(g->mlx, g->world.img);
	free(g->map->c_pos);
	free_ttmap(g->map);
	if (g->win.win)
		mlx_destroy_window(g->mlx, g->win.win);
	//mlx_destroy_display(g->mlx);
	if (g->mlx)
		free(g->mlx);
	free(g);
	exit(0);
}
