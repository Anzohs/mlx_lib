/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:52:13 by hladeiro          #+#    #+#             */
/*   Updated: 2024/09/06 00:17:10 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

void	free_data(t_game *game)
{
	mlx_destroy_window(game->data->mlx, game->data->win);
	free(game->data->mlx);
	free(game->map);
	free(game->data);
	free(game);
}

int	ft_update(t_game *game)
{
	printf("game address: %p\n", game);
	return (0);
}

int	ft_key_press(int keycode, t_game *game)
{
	if (keycode == 53)
	{
		free_data(game);
		exit(0);
	}
	return (0);
}
