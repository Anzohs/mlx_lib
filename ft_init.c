/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 23:17:47 by hladeiro          #+#    #+#             */
/*   Updated: 2024/09/06 00:18:38 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
 * Function: ft_init_game
 * ---------------------
 *  Initialize the main struct of the game t_game
 *
 *  @params: void
 *
 *
 *  @return: t_game struct
 *  Warning:
 *	- uses calloc to allocate memory!
 * */
t_game	*ft_init_game(void)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		return (NULL);
	game->data = ft_init_data();
	if (!game->data)
		return (NULL);
	game->map = ft_init_map();
	if (!game->map)
		return (NULL);
	game->init = ft_start_game;
	game->update = ft_update;
	return (game);
}

/*
 * Function: ft_init_map
 * ---------------------
 *  Initialize the main struct of the game t_map
 *
 *  params: void
 *
 *  return: t_map struct
 *  Warning:
 *	- uses calloc to allocate memory!
 */
t_map	*ft_init_map(void)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	map->pos = ft_init_vector(0, 0);
	return (map);
}

/*
 * Function: ft_init_dataa
 * ---------------------
 *  Initialize the main struct of the game t_data
 *
 *  params: void
 *
 *  return: t_data struct
 *  Warning:
 *	- uses calloc to allocate memory!
 */
t_data	*ft_init_data(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->mlx = mlx_init();
	if (!data->mlx)
		return (NULL);
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "so_long");
	if (!data->win)
		return (NULL);
	return (data);
}

/*
 * Function: ft_init_vector
 * ---------------------
 *  Initialize the main struct of the game t_vector
 *
 *  @params: void
 *
 *  @return: t_vector struct
 *  Warning:
 *	- uses calloc to allocate memory!
 */
t_vector	*ft_init_vector(int x, int y)
{
	t_vector	*vector;

	vector = ft_calloc(1, sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->x = x;
	vector->y = y;
	return (vector);
}

t_fvector	*ft_init_fvector(float x, float y)
{
	t_fvector	*vector;

	vector = ft_calloc(1, sizeof(t_vector));
	if (!vector)
		return (NULL);
	vector->x = x;
	vector->y = y;
	return (vector);
}
