/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:14:17 by hladeiro          #+#    #+#             */
/*   Updated: 2024/10/23 17:06:20 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include "map.h"
# include "cam.h"
# include "world.h"
# include "player.h"
# include "../mlx/mlx.h"
# include "libft/libft.h"

typedef struct s_map	t_map;

void	game_start(t_map map);

t_game	*init_game(char *name, t_vector s);
double	get_delta(void);
void	put_pixel(t_game *img, int x, int y, unsigned int color);
int		exit_t(t_game *g);

#endif
