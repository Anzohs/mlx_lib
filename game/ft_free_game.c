# include "../inc/game.h"

static void	img_destroy(void *mlx, void *img)
{
	if (img)
		mlx_destroy_image(mlx, img);
}

static void	destroy_collectibles(t_col *c, void *mlx, int n)
{
	int i;

	i = -1;
	while (++i < n)
	{
		img_destroy(mlx, c->c[i].current.img);
	}
}

static void	free_tmap(t_map *m)
{
	int	i;

	i = -1;
	while (++i < m->size.y)
		free(m->map[i]);
	free(m->map[i]);
	free(m);
}

void	ft_free_game(t_game *g, int e)
{
	if (e)
		ft_putstr_fd("Fail to allocate memory \n", 2);

	img_destroy(g->mlx, g->p.current.img);
	img_destroy(g->mlx, g->p.sprite.img);
	img_destroy(g->mlx, g->cam.img);
	img_destroy(g->mlx, g->i_map.floor.img);
	img_destroy(g->mlx, g->i_map.wall.img);
	img_destroy(g->mlx, g->world.img);
	free_map(g->map);
	mlx_destroy_window(g->mlx, g->win.win);
	//mlx_destroy_display(g->mlx);
	free(g);
}
