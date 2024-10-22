/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:06:51 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/21 19:08:00 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "mlx/mlx.h"
#include "structs.h"

char **create_map()
{
    char **map = malloc(sizeof(char *) * 5);
    map[0] = ft_strdup("00000");
    map[1] = ft_strdup("01110");
    map[2] = ft_strdup("01210");
    map[3] = ft_strdup("01110");
    map[4] = ft_strdup("00000");
    return (map);
}

void put_pixel(t_img *img, int x, int y, int color)
{
    char *dst;
    dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
    *(unsigned int *)dst = color;
}

void render_map(t_game *g)
{
    int x, y;
    int i, j;
    int tile_size = 32;

    y = -1;
    while (++y < 5)
    {
        x = -1;
        while (++x < 5)
        {
            int color;
            if (g->map[y][x] == '0')
                color = 0x000000;
            else if (g->map[y][x] == '1')
                color = 0xFFFFFF;
            else if (g->map[y][x] == '2')
                color = 0xFF0000;
            i = -1;
            while (++i < tile_size)
            {
                j = -1;
                while (++j < tile_size)
                    put_pixel(&g->cam, x * tile_size + i, y * tile_size + j, color);
            }
        }
    }
}

void	free_map(t_game *g)
{
	int i = -1;

	while (++i < 5)
		free(g->map[i]);
	free(g->map);
}

int	handle(int key, t_game *g)
{
	t_vector new = g->p.pos;

	if (key == 119)
		new.y--;
	else if (key == 115)
		new.y++;
	else if (key == 97)
		new.x--;
	else if (key == 100)
		new.x++;
	if (key == 65307)
	{
		free_map(g);
		exit_t(g);
	}
	if (g->map[new.y][new.x] == '1')
	{
		g->map[g->p.pos.y][g->p.pos.x] = '1';
		g->p.pos = new;
		g->map[g->p.pos.y][g->p.pos.x] = '2';
	}
	printf("::: %i ::: \n", key);
	return key;
}

int render(t_game *game)
{
    game->cam.img = mlx_new_image(game->mlx, game->size.x, game->size.y);
    game->cam.addr = mlx_get_data_addr(game->cam.img, &game->cam.bpp, &game->cam.line_len, &game->cam.endian);
    render_map(game);
    mlx_put_image_to_window(game->mlx, game->win.win, game->cam.img, 0, 0);
    mlx_destroy_image(game->mlx, game->cam.img);
    game->cam = (t_img){0};
    game->cam.pos = game->size;
    return (1);
}

void game_loop(t_game *game)
{
    mlx_key_hook(game->win.win, handle, game);
    mlx_loop_hook(game->mlx, &render, game);
    mlx_loop(game->mlx);
}

int main()
{
    t_game *g;
    g = init_game("test", (t_vector){1800, 1200});
    g->map = create_map();
	g->cam = (t_img){0};
	g->p = (t_player){0};
	g->p.pos = (t_vector){2, 2};
    g->cam.img = mlx_new_image(g->mlx, g->size.x, g->size.y); // Fixed dimensions
    mlx_put_image_to_window(g->mlx, g->win.win, g->cam.img, 0, 0);
    mlx_destroy_image(g->mlx, g->cam.img);
    g->cam = (t_img){0};
    g->cam.pos = g->size;
    g->loop = &game_loop;
    g->loop(g);
}
