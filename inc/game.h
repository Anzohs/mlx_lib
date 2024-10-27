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

# include <stdlib.h>
# include <stdbool.h>
# include <time.h>
# include "map.h"
# include "cam.h"
# include "structs.h"
# include "world.h"
# include "player.h"
# include "event.h"
# include "../mlx/mlx.h"
# include "libft/libft.h"

typedef struct s_map	t_map;

void	game_start(t_map map);

t_game	*init_game(char *name, t_vector s);
double	get_delta(void);
int		exit_t(t_game *g);
int		update_game(t_game *g, double dt);

#endif
