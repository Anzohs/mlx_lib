/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 19:34:36 by hladeiro          #+#    #+#             */
/*   Updated: 2024/09/05 23:32:44 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

/*
 * Function: ft_start_game
 * -----------------------
 *  Initialize the game Loop of mlx library
 *
 *  params: t_game *game
 * */
void	ft_start_game(t_game *game)
{
	mlx_hook(game->data->win, 2, 1L << 0, ft_key_press, game);
	mlx_loop_hook(game->data->mlx, game->update, game);
	mlx_loop(game->data->mlx);
}

/*
 * Function: main
 * -----------------------
 *  Initialize the main structure of the game t_game (from structs.h)
 *  and call the init function of the game
 * params: void
 * return: 0
 * */
int	main(void)
{
	t_game	*game;

	game = ft_init_game();
	game->init(game);
	return (0);
}
